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
struct zd1201 {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 short le16_to_cpu (int /*<<< orphan*/ ) ; 
 int zd1201_getconfig (struct zd1201*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int zd1201_getconfig16(struct zd1201 *zd, int rid, short *val)
{
	int err;
	__le16 zdval;

	err = zd1201_getconfig(zd, rid, &zdval, sizeof(__le16));
	if (err)
		return err;
	*val = le16_to_cpu(zdval);
	return 0;
}