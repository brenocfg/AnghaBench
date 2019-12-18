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
typedef  int u8 ;
struct esp {int config1; int scsi_id; int config2; int prev_cfg3; scalar_t__ cfact; int /*<<< orphan*/  rev; int /*<<< orphan*/  sync_defp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP100 ; 
 int /*<<< orphan*/  ESP100A ; 
 int /*<<< orphan*/  ESP236 ; 
 scalar_t__ ESP_CCF_F5 ; 
 int /*<<< orphan*/  ESP_CFG2 ; 
 int /*<<< orphan*/  ESP_CFG3 ; 
 int ESP_CONFIG1_PENABLE ; 
 int ESP_CONFIG2_MAGIC ; 
 int ESP_CONFIG2_REGPARITY ; 
 int ESP_CONFIG2_SCSI2ENAB ; 
 int /*<<< orphan*/  FAST ; 
 int /*<<< orphan*/  SYNC_DEFP_FAST ; 
 int esp_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_set_all_config3 (struct esp*,int) ; 
 int /*<<< orphan*/  esp_write8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_get_revision(struct esp *esp)
{
	u8 val;

	esp->config1 = (ESP_CONFIG1_PENABLE | (esp->scsi_id & 7));
	esp->config2 = (ESP_CONFIG2_SCSI2ENAB | ESP_CONFIG2_REGPARITY);
	esp_write8(esp->config2, ESP_CFG2);

	val = esp_read8(ESP_CFG2);
	val &= ~ESP_CONFIG2_MAGIC;
	if (val != (ESP_CONFIG2_SCSI2ENAB | ESP_CONFIG2_REGPARITY)) {
		/* If what we write to cfg2 does not come back, cfg2 is not
		 * implemented, therefore this must be a plain esp100.
		 */
		esp->rev = ESP100;
	} else {
		esp->config2 = 0;
		esp_set_all_config3(esp, 5);
		esp->prev_cfg3 = 5;
		esp_write8(esp->config2, ESP_CFG2);
		esp_write8(0, ESP_CFG3);
		esp_write8(esp->prev_cfg3, ESP_CFG3);

		val = esp_read8(ESP_CFG3);
		if (val != 5) {
			/* The cfg2 register is implemented, however
			 * cfg3 is not, must be esp100a.
			 */
			esp->rev = ESP100A;
		} else {
			esp_set_all_config3(esp, 0);
			esp->prev_cfg3 = 0;
			esp_write8(esp->prev_cfg3, ESP_CFG3);

			/* All of cfg{1,2,3} implemented, must be one of
			 * the fas variants, figure out which one.
			 */
			if (esp->cfact == 0 || esp->cfact > ESP_CCF_F5) {
				esp->rev = FAST;
				esp->sync_defp = SYNC_DEFP_FAST;
			} else {
				esp->rev = ESP236;
			}
			esp->config2 = 0;
			esp_write8(esp->config2, ESP_CFG2);
		}
	}
}