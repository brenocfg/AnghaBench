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
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_cb_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_sk (struct sock*) ; 

__attribute__((used)) static void ax25_free_sock(struct sock *sk)
{
	ax25_cb_put(ax25_sk(sk));
}