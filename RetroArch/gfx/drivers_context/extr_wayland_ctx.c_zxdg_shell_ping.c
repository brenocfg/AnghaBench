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
typedef  int /*<<< orphan*/  uint32_t ;
struct zxdg_shell_v6 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zxdg_shell_v6_pong (struct zxdg_shell_v6*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zxdg_shell_ping(void *data,
      struct zxdg_shell_v6 *shell, uint32_t serial)
{
    zxdg_shell_v6_pong(shell, serial);
}