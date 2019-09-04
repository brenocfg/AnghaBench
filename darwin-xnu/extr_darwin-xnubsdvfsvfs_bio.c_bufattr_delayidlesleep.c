#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bufattr_t ;
struct TYPE_3__ {int ba_flags; } ;

/* Variables and functions */
 int BA_DELAYIDLESLEEP ; 

int
#if !CONFIG_EMBEDDED
bufattr_delayidlesleep(bufattr_t bap) 
#else /* !CONFIG_EMBEDDED */
bufattr_delayidlesleep(__unused bufattr_t bap) 
#endif /* !CONFIG_EMBEDDED */
{
#if !CONFIG_EMBEDDED
	if ( (bap->ba_flags & BA_DELAYIDLESLEEP) )
		return 1;
#endif /* !CONFIG_EMBEDDED */
	return 0;
}