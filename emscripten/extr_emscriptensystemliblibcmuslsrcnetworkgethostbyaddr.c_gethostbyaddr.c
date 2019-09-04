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
struct hostent {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  NO_RECOVERY ; 
 int /*<<< orphan*/  free (struct hostent*) ; 
 int gethostbyaddr_r (void const*,int /*<<< orphan*/ ,int,struct hostent*,void*,size_t,struct hostent**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h_errno ; 
 struct hostent* malloc (size_t) ; 

struct hostent *gethostbyaddr(const void *a, socklen_t l, int af)
{
	static struct hostent *h;
	size_t size = 63;
	struct hostent *res;
	int err;
	do {
		free(h);
		h = malloc(size+=size+1);
		if (!h) {
			h_errno = NO_RECOVERY;
			return 0;
		}
		err = gethostbyaddr_r(a, l, af, h,
			(void *)(h+1), size-sizeof *h, &res, &h_errno);
	} while (err == ERANGE);
	return err ? 0 : h;
}