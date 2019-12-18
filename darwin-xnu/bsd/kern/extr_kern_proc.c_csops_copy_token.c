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
typedef  int user_size_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  length32 ;
typedef  int /*<<< orphan*/  fakeheader ;

/* Variables and functions */
 int ERANGE ; 
 int copyout (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
csops_copy_token(void *start, size_t length, user_size_t usize, user_addr_t uaddr)
{
	char fakeheader[8] = { 0 };
	int error;

	if (usize < sizeof(fakeheader))
		return ERANGE;

	/* if no blob, fill in zero header */
	if (NULL == start) {
		start = fakeheader;
		length = sizeof(fakeheader);
	} else if (usize < length) {
		/* ... if input too short, copy out length of entitlement */
		uint32_t length32 = htonl((uint32_t)length);
		memcpy(&fakeheader[4], &length32, sizeof(length32));
		
		error = copyout(fakeheader, uaddr, sizeof(fakeheader));
		if (error == 0)
			return ERANGE; /* input buffer to short, ERANGE signals that */
		return error;
	}
	return copyout(start, uaddr, length);
}