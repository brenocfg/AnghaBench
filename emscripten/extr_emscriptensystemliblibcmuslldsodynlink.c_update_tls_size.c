#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pthread {int dummy; } ;
struct TYPE_2__ {int tls_cnt; int tls_align; int /*<<< orphan*/  tls_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (scalar_t__,int) ; 
 TYPE_1__ libc ; 
 int tls_align ; 
 int tls_cnt ; 
 scalar_t__ tls_offset ; 

__attribute__((used)) static void update_tls_size()
{
	libc.tls_cnt = tls_cnt;
	libc.tls_align = tls_align;
	libc.tls_size = ALIGN(
		(1+tls_cnt) * sizeof(void *) +
		tls_offset +
		sizeof(struct pthread) +
		tls_align * 2,
	tls_align);
}