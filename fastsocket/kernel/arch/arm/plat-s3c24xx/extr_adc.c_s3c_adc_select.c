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
struct s3c_adc_client {int /*<<< orphan*/  channel; int /*<<< orphan*/  is_ts; int /*<<< orphan*/  (* select_cb ) (struct s3c_adc_client*,int) ;} ;
struct adc_device {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ S3C2410_ADCCON ; 
 unsigned int S3C2410_ADCCON_MUXMASK ; 
 unsigned int S3C2410_ADCCON_SELMUX (int /*<<< orphan*/ ) ; 
 unsigned int S3C2410_ADCCON_STARTMASK ; 
 unsigned int S3C2410_ADCCON_STDBM ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct s3c_adc_client*,int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void s3c_adc_select(struct adc_device *adc,
				  struct s3c_adc_client *client)
{
	unsigned con = readl(adc->regs + S3C2410_ADCCON);

	client->select_cb(client, 1);

	con &= ~S3C2410_ADCCON_MUXMASK;
	con &= ~S3C2410_ADCCON_STDBM;
	con &= ~S3C2410_ADCCON_STARTMASK;

	if (!client->is_ts)
		con |= S3C2410_ADCCON_SELMUX(client->channel);

	writel(con, adc->regs + S3C2410_ADCCON);
}