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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct aic26 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aic26_dai ; 
 struct aic26* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct aic26*) ; 
 int /*<<< orphan*/  snd_soc_unregister_dai (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aic26_spi_remove(struct spi_device *spi)
{
	struct aic26 *aic26 = dev_get_drvdata(&spi->dev);

	snd_soc_unregister_dai(&aic26_dai);
	kfree(aic26);

	return 0;
}