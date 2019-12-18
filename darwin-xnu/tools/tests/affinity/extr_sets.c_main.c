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
struct TYPE_7__ {int* data; } ;
typedef  TYPE_2__ work_t ;
struct TYPE_6__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  waiters; int /*<<< orphan*/  cnd; int /*<<< orphan*/  mtx; } ;
struct TYPE_8__ {int stagenum; char* name; int /*<<< orphan*/  thread; TYPE_1__ bufq; TYPE_1__* output; TYPE_1__* input; int /*<<< orphan*/ * fn; TYPE_4__* set; } ;
typedef  TYPE_3__ stage_info_t ;
struct TYPE_9__ {int setnum; int isize; int* data; TYPE_3__** stage; } ;
typedef  TYPE_4__ line_info_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int WORKERS_MAX ; 
 int affinity ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  auto_config (int,int*,int*) ; 
 int /*<<< orphan*/  barrier ; 
 void* cache_config ; 
 int /*<<< orphan*/ * consumer_fnp ; 
 int /*<<< orphan*/  err (int,char*,int,int) ; 
 int /*<<< orphan*/  funnel ; 
 int getopt (int,char**,char*) ; 
 void* halting ; 
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
	int			pages = 256; /* 1MB */
	int			buffers = 2;
	int			sets = 2;
	int			stages = 2;
	int			*status;
	line_info_t		*line_info;
	line_info_t		*lp;
	stage_info_t		*stage_info;
	stage_info_t		*sp;
	kern_return_t		ret;
	int			c;

	/* Do switch parsing: */
	while ((c = getopt (argc, argv, "ab:chi:p:s:twv:")) != -1) {
		switch (c) {
		case 'a':
			affinity = !affinity;
			break;
		case 'b':
			buffers = atoi(optarg);
			break;
		case 'c':
			cache_config = TRUE;
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
		case '?':
		case 'h':
		default:
			usage();
		}
	}
	argc -= optind; argv += optind;
	if (argc > 0)
		sets = atoi(*argv);

	if (cache_config)
		auto_config(pages, &buffers, &sets);

	pthread_mutex_init(&funnel, NULL);
	pthread_cond_init(&barrier, NULL);

	/*
 	 * Fire up the worker threads.
	 */
	threads = sets * stages;
	mutter("Launching %d set%s of %d threads with %saffinity, "
			"consumer reads%s data\n",
		sets, s_if_plural(sets), stages, affinity? "": "no ",
		(consumer_fnp == &reader_writer_fn)? " and writes" : "");
	if (pages < 256)
		mutter("  %dkB bytes per buffer, ", pages * 4);
	else
		mutter("  %dMB bytes per buffer, ", pages / 256);
	mutter("%d buffer%s per set ",
		buffers, s_if_plural(buffers));
	if (buffers * pages < 256)
		mutter("(total %dkB)\n", buffers * pages * 4);
	else
		mutter("(total %dMB)\n", buffers * pages / 256);
	mutter("  processing %d buffer%s...\n",
		iterations, s_if_plural(iterations));
	line_info = (line_info_t *) malloc(sets * sizeof(line_info_t));
	stage_info = (stage_info_t *) malloc(sets * stages * sizeof(stage_info_t));
	for (i = 0; i < sets; i++) {
		work_t	*work_array;

		lp = &line_info[i];

		lp->setnum = i + 1;
		lp->isize = pages * 4096 / sizeof(int);
		lp->data = (int *) malloc(buffers * pages * 4096);

		/* Set up the queue for the workers of this thread set: */
		for (j = 0; j < stages; j++) {
			sp = &stage_info[(i*stages) + j];
			sp->stagenum = j;
			sp->set = lp;
			lp->stage[j] = sp;
			pthread_mutex_init(&sp->bufq.mtx, NULL);
			pthread_cond_init(&sp->bufq.cnd, NULL);
			TAILQ_INIT(&sp->bufq.queue);
			sp->bufq.waiters = FALSE;
		}

		/*
		 * Take a second pass through the stages
		 * to define what the workers are and to interconnect their input/outputs
		 */
		for (j = 0; j < stages; j++) {
			sp = lp->stage[j];
			if (j == 0) {
				sp->fn = producer_fnp;
				sp->name = "producer";
			} else {
				sp->fn = consumer_fnp;
				sp->name = "consumer";
			}
			sp->input = &lp->stage[j]->bufq;
			sp->output = &lp->stage[(j + 1) % stages]->bufq;
		}

		/* Set up the buffers on the first worker of the set. */
		work_array = (work_t *)  malloc(buffers * sizeof(work_t));
		for (j = 0; j < buffers; j++) {
			work_array[j].data = lp->data + (lp->isize * j);	
			TAILQ_INSERT_TAIL(&lp->stage[0]->bufq.queue, &work_array[j], link);
			DBG("  empty work item %p for set %d data %p\n",
				&work_array[j], i, work_array[j].data);
		}

		/* Create this set of threads */
		for (j = 0; j < stages; j++) {
			if (ret = pthread_create(&lp->stage[j]->thread, NULL,
					&manager_fn,
					(void *) lp->stage[j]))
			err(1, "pthread_create %d,%d", i, j);
		}
	}

	/*
	 * We sit back anf wait for the slave to finish.
	 */
	for (i = 0; i < sets; i++) {
		lp = &line_info[i];
		for (j = 0; j < stages; j++) {
			if(ret = pthread_join(lp->stage[j]->thread, (void **)&status))
			    err(1, "pthread_join %d,%d", i, j);
			DBG("Thread %d,%d status %d\n", i, j, status);
		}
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