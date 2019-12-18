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
struct TYPE_4__ {size_t dupfd; } ;
struct TYPE_3__ {int fd; int type; char* expfname; } ;
union node {TYPE_2__ ndup; TYPE_1__ nfile; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cflag ; 
 int EEXIST ; 
#define  NAPPEND 136 
#define  NCLOBBER 135 
#define  NFROM 134 
#define  NFROMFD 133 
#define  NFROMTO 132 
#define  NHERE 131 
#define  NTO 130 
#define  NTOFD 129 
#define  NXHERE 128 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  close (int) ; 
 int dup2 (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int fstat (int,struct stat*) ; 
 int open (char const*,int,...) ; 
 int openhere (union node*) ; 
 int stat (char const*,struct stat*) ; 
 char* strerror (int) ; 

__attribute__((used)) static void
openredirect(union node *redir, char memory[10])
{
	struct stat sb;
	int fd = redir->nfile.fd;
	const char *fname;
	int f;
	int e;

	memory[fd] = 0;
	switch (redir->nfile.type) {
	case NFROM:
		fname = redir->nfile.expfname;
		if ((f = open(fname, O_RDONLY)) < 0)
			error("cannot open %s: %s", fname, strerror(errno));
		break;
	case NFROMTO:
		fname = redir->nfile.expfname;
		if ((f = open(fname, O_RDWR|O_CREAT, 0666)) < 0)
			error("cannot create %s: %s", fname, strerror(errno));
		break;
	case NTO:
		if (Cflag) {
			fname = redir->nfile.expfname;
			if (stat(fname, &sb) == -1) {
				if ((f = open(fname, O_WRONLY|O_CREAT|O_EXCL, 0666)) < 0)
					error("cannot create %s: %s", fname, strerror(errno));
			} else if (!S_ISREG(sb.st_mode)) {
				if ((f = open(fname, O_WRONLY, 0666)) < 0)
					error("cannot create %s: %s", fname, strerror(errno));
				if (fstat(f, &sb) != -1 && S_ISREG(sb.st_mode)) {
					close(f);
					error("cannot create %s: %s", fname,
					    strerror(EEXIST));
				}
			} else
				error("cannot create %s: %s", fname,
				    strerror(EEXIST));
			break;
		}
		/* FALLTHROUGH */
	case NCLOBBER:
		fname = redir->nfile.expfname;
		if ((f = open(fname, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)
			error("cannot create %s: %s", fname, strerror(errno));
		break;
	case NAPPEND:
		fname = redir->nfile.expfname;
		if ((f = open(fname, O_WRONLY|O_CREAT|O_APPEND, 0666)) < 0)
			error("cannot create %s: %s", fname, strerror(errno));
		break;
	case NTOFD:
	case NFROMFD:
		if (redir->ndup.dupfd >= 0) {	/* if not ">&-" */
			if (memory[redir->ndup.dupfd])
				memory[fd] = 1;
			else {
				if (dup2(redir->ndup.dupfd, fd) < 0)
					error("%d: %s", redir->ndup.dupfd,
							strerror(errno));
			}
		} else {
			close(fd);
		}
		return;
	case NHERE:
	case NXHERE:
		f = openhere(redir);
		break;
	default:
		abort();
	}
	if (f != fd) {
		if (dup2(f, fd) == -1) {
			e = errno;
			close(f);
			error("%d: %s", fd, strerror(e));
		}
		close(f);
	}
}