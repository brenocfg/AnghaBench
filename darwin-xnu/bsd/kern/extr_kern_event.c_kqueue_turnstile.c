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
struct turnstile {int dummy; } ;
struct kqueue {int dummy; } ;

/* Variables and functions */
 struct turnstile* kqueue_get_turnstile (struct kqueue*,int) ; 

struct turnstile *
kqueue_turnstile(struct kqueue *kq)
{
	return kqueue_get_turnstile(kq, false);
}