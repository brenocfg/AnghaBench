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
typedef  int /*<<< orphan*/  u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 unsigned long CLASS_CODE_SCTP_IPV6 ; 
 unsigned long CLASS_CODE_USER_PROG1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  TCAM_KEY (unsigned long) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_set_tcam_key(struct niu *np, unsigned long class_code, u64 key)
{
	if (class_code < CLASS_CODE_USER_PROG1 ||
	    class_code > CLASS_CODE_SCTP_IPV6)
		return -EINVAL;

	nw64(TCAM_KEY(class_code - CLASS_CODE_USER_PROG1), key);
	return 0;
}