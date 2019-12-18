#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_ac97 {int dummy; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 int AC_CMD_ADDR (unsigned short) ; 
 int AC_CMD_DATA (unsigned short) ; 
 scalar_t__ S3C_AC97_CODEC_CMD ; 
 int S3C_AC97_CODEC_CMD_READ ; 
 scalar_t__ S3C_AC97_GLBCTRL ; 
 int S3C_AC97_GLBCTRL_CODECREADYIE ; 
 int /*<<< orphan*/  S3C_AC97_GLBSTAT_CODECREADY ; 
 int /*<<< orphan*/  ac97_completion ; 
 int /*<<< orphan*/  ac97_mutex ; 
 int /*<<< orphan*/  codec_ready ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 TYPE_1__ s3c24xx_ac97 ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s3c2443_ac97_write(struct snd_ac97 *ac97, unsigned short reg,
	unsigned short val)
{
	u32 ac_glbctrl;
	u32 ac_codec_cmd;

	mutex_lock(&ac97_mutex);

	codec_ready = S3C_AC97_GLBSTAT_CODECREADY;
	ac_codec_cmd = readl(s3c24xx_ac97.regs + S3C_AC97_CODEC_CMD);
	ac_codec_cmd = AC_CMD_ADDR(reg) | AC_CMD_DATA(val);
	writel(ac_codec_cmd, s3c24xx_ac97.regs + S3C_AC97_CODEC_CMD);

	udelay(50);

	ac_glbctrl = readl(s3c24xx_ac97.regs + S3C_AC97_GLBCTRL);
	ac_glbctrl |= S3C_AC97_GLBCTRL_CODECREADYIE;
	writel(ac_glbctrl, s3c24xx_ac97.regs + S3C_AC97_GLBCTRL);

	wait_for_completion(&ac97_completion);

	ac_codec_cmd = readl(s3c24xx_ac97.regs + S3C_AC97_CODEC_CMD);
	ac_codec_cmd |= S3C_AC97_CODEC_CMD_READ;
	writel(ac_codec_cmd, s3c24xx_ac97.regs + S3C_AC97_CODEC_CMD);

	mutex_unlock(&ac97_mutex);

}