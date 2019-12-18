#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dupfd; } ;
struct TYPE_3__ {int fd; scalar_t__ type; union node* next; } ;
union node {TYPE_2__ ndup; TYPE_1__ nfile; } ;
struct redirtab {int* renamed; int fd0_redirected; struct redirtab* next; scalar_t__ empty_redirs; } ;

/* Variables and functions */
 int CLOSED ; 
#define  EBADF 128 
 int EMPTY ; 
 int /*<<< orphan*/  F_DUPFD_CLOEXEC ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 scalar_t__ NFROMFD ; 
 scalar_t__ NTOFD ; 
 int REDIR_BACKQ ; 
 int REDIR_PUSH ; 
 struct redirtab* ckmalloc (int) ; 
 scalar_t__ empty_redirs ; 
 int errno ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int fd0_redirected ; 
 int /*<<< orphan*/  memout ; 
 int /*<<< orphan*/  openredirect (union node*,char*) ; 
 int /*<<< orphan*/ * out1 ; 
 int /*<<< orphan*/ * out2 ; 
 struct redirtab* redirlist ; 
 char* strerror (int) ; 

void
redirect(union node *redir, int flags)
{
	union node *n;
	struct redirtab *sv = NULL;
	int i;
	int fd;
	char memory[10];	/* file descriptors to write to memory */

	INTOFF;
	for (i = 10 ; --i >= 0 ; )
		memory[i] = 0;
	memory[1] = flags & REDIR_BACKQ;
	if (flags & REDIR_PUSH) {
		empty_redirs++;
		if (redir != NULL) {
			sv = ckmalloc(sizeof (struct redirtab));
			for (i = 0 ; i < 10 ; i++)
				sv->renamed[i] = EMPTY;
			sv->fd0_redirected = fd0_redirected;
			sv->empty_redirs = empty_redirs - 1;
			sv->next = redirlist;
			redirlist = sv;
			empty_redirs = 0;
		}
	}
	for (n = redir ; n ; n = n->nfile.next) {
		fd = n->nfile.fd;
		if (fd == 0)
			fd0_redirected = 1;
		if ((n->nfile.type == NTOFD || n->nfile.type == NFROMFD) &&
		    n->ndup.dupfd == fd)
			continue; /* redirect from/to same file descriptor */

		if ((flags & REDIR_PUSH) && sv->renamed[fd] == EMPTY) {
			INTOFF;
			if ((i = fcntl(fd, F_DUPFD_CLOEXEC, 10)) == -1) {
				switch (errno) {
				case EBADF:
					i = CLOSED;
					break;
				default:
					INTON;
					error("%d: %s", fd, strerror(errno));
					break;
				}
			}
			sv->renamed[fd] = i;
			INTON;
		}
		openredirect(n, memory);
		INTON;
		INTOFF;
	}
	if (memory[1])
		out1 = &memout;
	if (memory[2])
		out2 = &memout;
	INTON;
}