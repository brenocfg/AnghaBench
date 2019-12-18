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
struct fibheap {int dummy; } ;
typedef  int /*<<< orphan*/  fibheap_t ;

/* Variables and functions */
 int /*<<< orphan*/  xcalloc (int,int) ; 

fibheap_t
fibheap_new (void)
{
  return (fibheap_t) xcalloc (1, sizeof (struct fibheap));
}