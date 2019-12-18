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
typedef  int /*<<< orphan*/  hrz_dev ;
typedef  int /*<<< orphan*/  HDW ;

/* Variables and functions */
 int /*<<< orphan*/  MEMORY_PORT_OFF ; 
 int /*<<< orphan*/  MEM_RD_ADDR_REG_OFF ; 
 int /*<<< orphan*/  rd_regl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_regl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u32 rd_mem (const hrz_dev * dev, HDW * addr) {
  // wr_regl (dev, MEM_RD_ADDR_REG_OFF, (u32) addr);
  wr_regl (dev, MEM_RD_ADDR_REG_OFF, (addr - (HDW *) 0) * sizeof(HDW));
  return rd_regl (dev, MEMORY_PORT_OFF);
}