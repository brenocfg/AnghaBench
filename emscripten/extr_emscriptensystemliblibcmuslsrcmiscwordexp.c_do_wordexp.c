#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t we_wordc; char** we_wordv; int we_offs; } ;
typedef  TYPE_1__ wordexp_t ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  SIGKILL ; 
 int SIZE_MAX ; 
 int WRDE_APPEND ; 
 int WRDE_BADCHAR ; 
 int WRDE_CMDSUB ; 
 int WRDE_DOOFFS ; 
 int WRDE_NOCMD ; 
 int WRDE_NOSPACE ; 
 int WRDE_REUSE ; 
 int WRDE_SHOWERR ; 
 int WRDE_SYNTAX ; 
 int /*<<< orphan*/  __block_all_sigs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __restore_sigs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit (int) ; 
 char** calloc (size_t,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  execl (char*,char*,char*,char*,char*,char const*,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getword (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pipe2 (int*,int /*<<< orphan*/ ) ; 
 char** realloc (char**,size_t) ; 
 int /*<<< orphan*/  reap (scalar_t__) ; 
 int /*<<< orphan*/  wordfree (TYPE_1__*) ; 

__attribute__((used)) static int do_wordexp(const char *s, wordexp_t *we, int flags)
{
	size_t i, l;
	int sq=0, dq=0;
	size_t np=0;
	char *w, **tmp;
	char *redir = (flags & WRDE_SHOWERR) ? "" : "2>/dev/null";
	int err = 0;
	FILE *f;
	size_t wc = 0;
	char **wv = 0;
	int p[2];
	pid_t pid;
	sigset_t set;

	if (flags & WRDE_REUSE) wordfree(we);

	if (flags & WRDE_NOCMD) for (i=0; s[i]; i++) switch (s[i]) {
	case '\\':
		if (!sq) i++;
		break;
	case '\'':
		if (!dq) sq^=1;
		break;
	case '"':
		if (!sq) dq^=1;
		break;
	case '(':
		if (np) {
			np++;
			break;
		}
	case ')':
		if (np) {
			np--;
			break;
		}
	case '\n':
	case '|':
	case '&':
	case ';':
	case '<':
	case '>':
	case '{':
	case '}':
		if (!(sq|dq|np)) return WRDE_BADCHAR;
		break;
	case '$':
		if (sq) break;
		if (s[i+1]=='(' && s[i+2]=='(') {
			i += 2;
			np += 2;
			break;
		} else if (s[i+1] != '(') break;
	case '`':
		if (sq) break;
		return WRDE_CMDSUB;
	}

	if (flags & WRDE_APPEND) {
		wc = we->we_wordc;
		wv = we->we_wordv;
	}

	i = wc;
	if (flags & WRDE_DOOFFS) {
		if (we->we_offs > SIZE_MAX/sizeof(void *)/4)
			goto nospace;
		i += we->we_offs;
	} else {
		we->we_offs = 0;
	}

	if (pipe2(p, O_CLOEXEC) < 0) goto nospace;
	__block_all_sigs(&set);
	pid = fork();
	__restore_sigs(&set);
	if (pid < 0) {
		close(p[0]);
		close(p[1]);
		goto nospace;
	}
	if (!pid) {
		if (p[1] == 1) fcntl(1, F_SETFD, 0);
		else dup2(p[1], 1);
		execl("/bin/sh", "sh", "-c",
			"eval \"printf %s\\\\\\\\0 x $1 $2\"",
			"sh", s, redir, (char *)0);
		_exit(1);
	}
	close(p[1]);
	
	f = fdopen(p[0], "r");
	if (!f) {
		close(p[0]);
		kill(pid, SIGKILL);
		reap(pid);
		goto nospace;
	}

	l = wv ? i+1 : 0;

	free(getword(f));
	if (feof(f)) {
		fclose(f);
		reap(pid);
		return WRDE_SYNTAX;
	}

	while ((w = getword(f))) {
		if (i+1 >= l) {
			l += l/2+10;
			tmp = realloc(wv, l*sizeof(char *));
			if (!tmp) break;
			wv = tmp;
		}
		wv[i++] = w;
		wv[i] = 0;
	}
	if (!feof(f)) err = WRDE_NOSPACE;

	fclose(f);
	reap(pid);

	if (!wv) wv = calloc(i+1, sizeof *wv);

	we->we_wordv = wv;
	we->we_wordc = i;

	if (flags & WRDE_DOOFFS) {
		if (wv) for (i=we->we_offs; i; i--)
			we->we_wordv[i-1] = 0;
		we->we_wordc -= we->we_offs;
	}
	return err;

nospace:
	if (!(flags & WRDE_APPEND)) {
		we->we_wordc = 0;
		we->we_wordv = 0;
	}
	return WRDE_NOSPACE;
}