#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int setnum; int /*<<< orphan*/  thread; TYPE_4__* stage; } ;
typedef  TYPE_2__ worker_info_t ;
struct TYPE_8__ {int* data; int isize; scalar_t__ tag; } ;
typedef  TYPE_3__ work_t ;
struct TYPE_6__ {int /*<<< orphan*/  queue; scalar_t__ waiters; int /*<<< orphan*/  cnd; int /*<<< orphan*/  mtx; } ;
struct TYPE_9__ {int stagenum; char* name; int work_todo; TYPE_1__ bufq; TYPE_1__* output; TYPE_1__* input; int /*<<< orphan*/ * fn; } ;
typedef  TYPE_4__ stage_info_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int WORKERS_MAX ; 
 int affinity ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  barrier ; 
 int /*<<< orphan*/ * consumer_fnp ; 
 int /*<<< orphan*/  err (int,char*,int,int) ; 
 int /*<<< orphan*/  funnel ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  halting ; 
 int iterations ; 
 int /*<<< orphan*/  link ; 
 unsigned long long mach_absolute_time () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  manager_fn ; 
 int /*<<< orphan*/  mutter (char*,int,...) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/ * producer_fnp ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_writer_fn ; 
 int /*<<< orphan*/  s_if_plural (int) ; 
 int threads ; 
 unsigned long long timer ; 
 int /*<<< orphan*/  usage () ; 
 void* verbosity ; 

int
main(int argc, char *argv[])
{
	int			i;
	int			j;
	int			k;
	int			pages = 256; /* 1MB */
	int			buffers = 2;
	int			producers = 2;
	int			consumers = 2;
	int			stages = 2;
	int			*status;
	stage_info_t		*stage_info;
	stage_info_t		*sp;
	worker_info_t		*worker_info;
	worker_info_t		*wp;
	kern_return_t		ret;
	int			c;

	/* Do switch parsing: */
	while ((c = getopt (argc, argv, "ab:i:p:s:twv:")) != -1) {
		switch (c) {
		case 'a':
			affinity = !affinity;
			break;
		case 'b':
			buffers = atoi(optarg);
			break;
		case 'i':
			iterations = atoi(optarg);
			break;
		case 'p':
			pages = atoi(optarg);
			break;
		case 's':
			stages = atoi(optarg);
			if (stages >= WORKERS_MAX)
				usage();
			break;
		case 't':
			halting = TRUE;
			break;
		case 'w':
			consumer_fnp = &reader_writer_fn;
			break;
		case 'v':
			verbosity = atoi(optarg);
			break;
		case 'h':
		case '?':
		default:
			usage();
		}
	}
	argc -= optind; argv += optind;
	if (argc > 0)
		producers = atoi(*argv);
	argc--; argv++;
	if (argc > 0)
		consumers = atoi(*argv);
	
	pthread_mutex_init(&funnel, NULL);
	pthread_cond_init(&barrier, NULL);

	/*
 	 * Fire up the worker threads.
	 */
	threads = consumers * (stages - 1) + producers;
	mutter("Launching %d producer%s with %d stage%s of %d consumer%s\n"
		"  with %saffinity, consumer reads%s data\n",
		producers, s_if_plural(producers),
		stages - 1, s_if_plural(stages - 1),
		consumers, s_if_plural(consumers),
		affinity? "": "no ",
		(consumer_fnp == &reader_writer_fn)? " and writes" : "");
	if (pages < 256)
		mutter("  %dkB bytes per buffer, ", pages * 4);
	else
		mutter("  %dMB bytes per buffer, ", pages / 256);
	mutter("%d buffer%s per producer ",
		buffers, s_if_plural(buffers));
	if (buffers * pages < 256)
		mutter("(total %dkB)\n", buffers * pages * 4);
	else
		mutter("(total %dMB)\n", buffers * pages / 256);
	mutter("  processing %d buffer%s...\n",
		iterations, s_if_plural(iterations));

	stage_info = (stage_info_t *) malloc(stages * sizeof(stage_info_t));
	worker_info = (worker_info_t *) malloc(threads * sizeof(worker_info_t));

	/* Set up the queue for the workers of this thread set: */
	for (i = 0; i < stages; i++) {
		sp = &stage_info[i];
		sp->stagenum = i;
		pthread_mutex_init(&sp->bufq.mtx, NULL);
		pthread_cond_init(&sp->bufq.cnd, NULL);
		TAILQ_INIT(&sp->bufq.queue);
		sp->bufq.waiters = 0;
		if (i == 0) {
			sp->fn = producer_fnp;
			sp->name = "producer";
		} else {
			sp->fn = consumer_fnp;
			sp->name = "consumer";
		}
		sp->input = &sp->bufq;
		sp->output = &stage_info[(i + 1) % stages].bufq;
		stage_info[i].work_todo = iterations;
	}
 
	/* Create the producers */
	for (i = 0; i < producers; i++) {
		work_t	*work_array;
		int	*data;
		int	isize;

		isize = pages * 4096 / sizeof(int);
		data = (int *) malloc(buffers * pages * 4096);

		/* Set up the empty work buffers */
		work_array = (work_t *)  malloc(buffers * sizeof(work_t));
		for (j = 0; j < buffers; j++) {
			work_array[j].data = data + (isize * j);	
			work_array[j].isize = isize;
			work_array[j].tag = 0;
			TAILQ_INSERT_TAIL(&stage_info[0].bufq.queue, &work_array[j], link);
			DBG("  empty work item %p for data %p\n",
				&work_array[j], work_array[j].data);
		}
		wp = &worker_info[i];
		wp->setnum = i + 1;
		wp->stage = &stage_info[0];
		if (ret = pthread_create(&wp->thread,
					 NULL,
					 &manager_fn,
					 (void *) wp))
			err(1, "pthread_create %d,%d", 0, i);
	}

	/* Create consumers */
	for (i = 1; i < stages; i++) {
		for (j = 0; j < consumers; j++) {
			wp = &worker_info[producers + (consumers*(i-1)) + j];
			wp->setnum = j + 1;
			wp->stage = &stage_info[i];
			if (ret = pthread_create(&wp->thread,
						NULL,
						&manager_fn,
						(void *) wp))
				err(1, "pthread_create %d,%d", i, j);
		}
	}

	/*
	 * We sit back anf wait for the slaves to finish.
	 */
	for (k = 0; k < threads; k++) {
		int	i;
		int	j;

		wp = &worker_info[k];
		if (k < producers) {
			i = 0;
			j = k;
		} else {
			i = (k - producers) / consumers;
			j = (k - producers) % consumers;
		}
		if(ret = pthread_join(wp->thread, (void **)&status))
		    err(1, "pthread_join %d,%d", i, j);
		DBG("Thread %d,%d status %d\n", i, j, status);
	}

	/*
	 * See how long the work took.
	 */
	timer = mach_absolute_time() - timer;
	timer = timer / 1000000ULL;
	printf("%d.%03d seconds elapsed.\n",
		(int) (timer/1000ULL), (int) (timer % 1000ULL));

	return 0;
}