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
struct s3cmci_host {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ S3C2410_SDIFSTA ; 
 int /*<<< orphan*/  S3C2410_SDIFSTA_COUNTMASK ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline u32 fifo_count(struct s3cmci_host *host)
{
	u32 fifostat = readl(host->base + S3C2410_SDIFSTA);

	fifostat &= S3C2410_SDIFSTA_COUNTMASK;
	return fifostat;
}