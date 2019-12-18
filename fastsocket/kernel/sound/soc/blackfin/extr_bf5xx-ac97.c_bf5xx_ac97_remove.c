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
struct snd_soc_dai {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SND_BF5XX_RESET_GPIO_NUM ; 
 int /*<<< orphan*/ * cmd_count ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peripheral_free_list (int /*<<< orphan*/ ) ; 
 size_t sport_num ; 
 int /*<<< orphan*/ * sport_req ; 

__attribute__((used)) static void bf5xx_ac97_remove(struct platform_device *pdev,
			      struct snd_soc_dai *dai)
{
	free_page((unsigned long)cmd_count);
	cmd_count = NULL;
	peripheral_free_list(sport_req[sport_num]);
#ifdef CONFIG_SND_BF5XX_HAVE_COLD_RESET
	gpio_free(CONFIG_SND_BF5XX_RESET_GPIO_NUM);
#endif
}