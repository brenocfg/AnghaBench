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
struct st5481_d_out {int /*<<< orphan*/  urb; } ;
struct st5481_adapter {struct st5481_d_out d_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 int /*<<< orphan*/  st5481_release_isocpipes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st5481_release_d_out(struct st5481_adapter *adapter)
{
	struct st5481_d_out *d_out = &adapter->d_out;

	DBG(2,"");

	st5481_release_isocpipes(d_out->urb);
}