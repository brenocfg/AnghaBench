#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct queue {int /*<<< orphan*/  queue; } ;
struct qitem {char* mailfn; } ;
struct dirent {char* d_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  spooldir; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EX_NOINPUT ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bzero (struct queue*,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 struct qitem* readqueuef (struct queue*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,char*) ; 

int
load_queue(struct queue *queue)
{
	struct stat sb;
	struct qitem *it;
	DIR *spooldir;
	struct dirent *de;
	char *queuefn;
	char *mailfn;

	bzero(queue, sizeof(*queue));
	LIST_INIT(&queue->queue);

	spooldir = opendir(config.spooldir);
	if (spooldir == NULL)
		err(EX_NOINPUT, "reading queue");

	while ((de = readdir(spooldir)) != NULL) {
		queuefn = NULL;
		mailfn = NULL;

		/* ignore non-queue files */
		if (de->d_name[0] != 'Q')
			continue;
		if (asprintf(&queuefn, "%s/Q%s", config.spooldir, de->d_name + 1) < 0)
			goto fail;
		if (asprintf(&mailfn, "%s/M%s", config.spooldir, de->d_name + 1) < 0)
			goto fail;

		/*
		 * Some file systems don't provide a de->d_type, so we have to
		 * do an explicit stat on the queue file.
		 * Move on if it turns out to be something else than a file.
		 */
		if (stat(queuefn, &sb) != 0)
			goto skip_item;
		if (!S_ISREG(sb.st_mode)) {
			errno = EINVAL;
			goto skip_item;
		}

		if (stat(mailfn, &sb) != 0)
			goto skip_item;

		it = readqueuef(queue, queuefn);
		if (it == NULL)
			goto skip_item;

		it->mailfn = mailfn;
		continue;

skip_item:
		syslog(LOG_INFO, "could not pick up queue file: `%s'/`%s': %m", queuefn, mailfn);
		if (queuefn != NULL)
			free(queuefn);
		if (mailfn != NULL)
			free(mailfn);
	}
	closedir(spooldir);
	return (0);

fail:
	return (-1);
}