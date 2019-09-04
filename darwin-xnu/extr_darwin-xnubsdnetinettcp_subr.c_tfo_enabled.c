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
struct tcpcb {int t_flagsext; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int TF_FASTOPEN ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
tfo_enabled(const struct tcpcb *tp)
{
	return ((tp->t_flagsext & TF_FASTOPEN)? TRUE : FALSE);
}