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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  FIX (char const*) ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int __getpw_a (char const*,int /*<<< orphan*/ ,struct passwd*,char**,size_t*,struct passwd**) ; 
 char const* dir ; 
 int /*<<< orphan*/  free (char*) ; 
 char const* gecos ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char const* passwd ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 
 char const* shell ; 

__attribute__((used)) static int getpw_r(const char *name, uid_t uid, struct passwd *pw, char *buf, size_t size, struct passwd **res)
{
	char *line = 0;
	size_t len = 0;
	int rv = 0;
	int cs;

	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);

	rv = __getpw_a(name, uid, pw, &line, &len, res);
	if (*res && size < len) {
		*res = 0;
		rv = ERANGE;
	}
	if (*res) {
		memcpy(buf, line, len);
		FIX(name);
		FIX(passwd);
		FIX(gecos);
		FIX(dir);
		FIX(shell);
	}
 	free(line);
	pthread_setcancelstate(cs, 0);
	return rv;
}