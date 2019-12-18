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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MC5_DB_DBGI_RSP_DATA0 ; 
 int /*<<< orphan*/  A_MC5_DB_DBGI_RSP_DATA1 ; 
 int /*<<< orphan*/  A_MC5_DB_DBGI_RSP_DATA2 ; 
 int /*<<< orphan*/  t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dbgi_rd_rsp3(struct adapter *adapter, u32 *v1, u32 *v2,
				u32 *v3)
{
	*v1 = t3_read_reg(adapter, A_MC5_DB_DBGI_RSP_DATA0);
	*v2 = t3_read_reg(adapter, A_MC5_DB_DBGI_RSP_DATA1);
	*v3 = t3_read_reg(adapter, A_MC5_DB_DBGI_RSP_DATA2);
}