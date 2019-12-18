#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qitem {int /*<<< orphan*/ * mailf; int /*<<< orphan*/ * queuef; int /*<<< orphan*/  queuefn; int /*<<< orphan*/  mailfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct qitem*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void
delqueue(struct qitem *it)
{
	unlink(it->mailfn);
	unlink(it->queuefn);
	if (it->queuef != NULL)
		fclose(it->queuef);
	if (it->mailf != NULL)
		fclose(it->mailf);
	free(it);
}