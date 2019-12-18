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
struct TYPE_4__ {int fd; int /*<<< orphan*/  fname; } ;
struct TYPE_3__ {scalar_t__ dupfd; } ;
union node {scalar_t__ type; TYPE_2__ nfile; TYPE_1__ ndup; } ;

/* Variables and functions */
 scalar_t__ NFROMFD ; 
 scalar_t__ NTOFD ; 
 int /*<<< orphan*/  cmdputs (char const*) ; 
 int /*<<< orphan*/  cmdtxt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cmdtxtredir(union node *n, const char *op, int deffd)
{
	char s[2];

	if (n->nfile.fd != deffd) {
		s[0] = n->nfile.fd + '0';
		s[1] = '\0';
		cmdputs(s);
	}
	cmdputs(op);
	if (n->type == NTOFD || n->type == NFROMFD) {
		if (n->ndup.dupfd >= 0)
			s[0] = n->ndup.dupfd + '0';
		else
			s[0] = '-';
		s[1] = '\0';
		cmdputs(s);
	} else {
		cmdtxt(n->nfile.fname);
	}
}