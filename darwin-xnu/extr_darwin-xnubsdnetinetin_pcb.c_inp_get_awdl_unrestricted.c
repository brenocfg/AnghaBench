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
struct inpcb {int inp_flags2; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int INP2_AWDL_UNRESTRICTED ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
inp_get_awdl_unrestricted(struct inpcb *inp)
{
	return (inp->inp_flags2 & INP2_AWDL_UNRESTRICTED) ? TRUE : FALSE;
}