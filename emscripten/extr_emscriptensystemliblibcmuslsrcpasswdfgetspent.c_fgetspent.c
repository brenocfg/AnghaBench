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
struct spwd {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PTHREAD_CANCEL_DISABLE ; 
 scalar_t__ __parsespent (char*,struct spwd*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 

struct spwd *fgetspent(FILE *f)
{
	static char *line;
	static struct spwd sp;
	size_t size = 0;
	struct spwd *res = 0;
	int cs;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	if (getline(&line, &size, f) >= 0 && __parsespent(line, &sp) >= 0) res = &sp;
	pthread_setcancelstate(cs, 0);
	return res;
}