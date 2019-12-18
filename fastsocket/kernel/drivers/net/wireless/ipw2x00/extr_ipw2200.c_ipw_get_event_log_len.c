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
typedef  int /*<<< orphan*/  u32 ;
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_EVENT_LOG ; 
 int /*<<< orphan*/  ipw_read32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_read_reg32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 ipw_get_event_log_len(struct ipw_priv *priv)
{
	/* length = 1st dword in log */
	return ipw_read_reg32(priv, ipw_read32(priv, IPW_EVENT_LOG));
}