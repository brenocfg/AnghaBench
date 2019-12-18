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
struct data {scalar_t__ len; scalar_t__ val; } ;

/* Variables and functions */
 struct data data_grow_for (struct data,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,int) ; 

struct data data_append_data(struct data d, const void *p, int len)
{
	d = data_grow_for(d, len);
	memcpy(d.val + d.len, p, len);
	d.len += len;
	return d;
}