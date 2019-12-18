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
struct qitem {char* queueid; char* sender; char* addr; int /*<<< orphan*/ * queuef; int /*<<< orphan*/  queuefn; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 scalar_t__ fchmod (int,int) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fprintf (int /*<<< orphan*/ *,char*,char*,char*,char*) ; 
 scalar_t__ fsync (int /*<<< orphan*/ ) ; 
 int open_locked (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
writequeuef(struct qitem *it)
{
	int error;
	int queuefd;

	queuefd = open_locked(it->queuefn, O_CREAT|O_EXCL|O_RDWR, 0660);
	if (queuefd == -1)
		return (-1);
	if (fchmod(queuefd, 0660) < 0)
		return (-1);
	it->queuef = fdopen(queuefd, "w+");
	if (it->queuef == NULL)
		return (-1);

	error = fprintf(it->queuef,
			"ID: %s\n"
			"Sender: %s\n"
			"Recipient: %s\n",
			 it->queueid,
			 it->sender,
			 it->addr);

	if (error <= 0)
		return (-1);

	if (fflush(it->queuef) != 0 || fsync(fileno(it->queuef)) != 0)
		return (-1);

	return (0);
}