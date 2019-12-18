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
typedef  int u32 ;
struct scsi_cmnd {int dummy; } ;
struct esp_cmd_entry {int flags; } ;
struct esp {int prev_cfg3; int sreg; scalar_t__ rev; int data_dma_len; int /*<<< orphan*/  prev_soff; } ;

/* Variables and functions */
 scalar_t__ ESP100 ; 
 int ESP_CMD_FLAG_WRITE ; 
 int ESP_CONFIG3_EWIDE ; 
 int ESP_DIP ; 
 int ESP_DOP ; 
 int /*<<< orphan*/  ESP_FFLAGS ; 
 int ESP_FF_FBYTES ; 
 int ESP_FF_ONOTZERO ; 
 int /*<<< orphan*/  ESP_STATUS ; 
 int ESP_STAT_PMASK ; 
 int ESP_STAT_TCNT ; 
 int /*<<< orphan*/  ESP_TCLOW ; 
 int /*<<< orphan*/  ESP_TCMED ; 
 scalar_t__ FASHME ; 
 int /*<<< orphan*/  FAS_RLO ; 
 int /*<<< orphan*/  esp_flush_fifo (struct esp*) ; 
 int esp_read8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp_data_bytes_sent(struct esp *esp, struct esp_cmd_entry *ent,
			       struct scsi_cmnd *cmd)
{
	int fifo_cnt, ecount, bytes_sent, flush_fifo;

	fifo_cnt = esp_read8(ESP_FFLAGS) & ESP_FF_FBYTES;
	if (esp->prev_cfg3 & ESP_CONFIG3_EWIDE)
		fifo_cnt <<= 1;

	ecount = 0;
	if (!(esp->sreg & ESP_STAT_TCNT)) {
		ecount = ((unsigned int)esp_read8(ESP_TCLOW) |
			  (((unsigned int)esp_read8(ESP_TCMED)) << 8));
		if (esp->rev == FASHME)
			ecount |= ((unsigned int)esp_read8(FAS_RLO)) << 16;
	}

	bytes_sent = esp->data_dma_len;
	bytes_sent -= ecount;

	if (!(ent->flags & ESP_CMD_FLAG_WRITE))
		bytes_sent -= fifo_cnt;

	flush_fifo = 0;
	if (!esp->prev_soff) {
		/* Synchronous data transfer, always flush fifo. */
		flush_fifo = 1;
	} else {
		if (esp->rev == ESP100) {
			u32 fflags, phase;

			/* ESP100 has a chip bug where in the synchronous data
			 * phase it can mistake a final long REQ pulse from the
			 * target as an extra data byte.  Fun.
			 *
			 * To detect this case we resample the status register
			 * and fifo flags.  If we're still in a data phase and
			 * we see spurious chunks in the fifo, we return error
			 * to the caller which should reset and set things up
			 * such that we only try future transfers to this
			 * target in synchronous mode.
			 */
			esp->sreg = esp_read8(ESP_STATUS);
			phase = esp->sreg & ESP_STAT_PMASK;
			fflags = esp_read8(ESP_FFLAGS);

			if ((phase == ESP_DOP &&
			     (fflags & ESP_FF_ONOTZERO)) ||
			    (phase == ESP_DIP &&
			     (fflags & ESP_FF_FBYTES)))
				return -1;
		}
		if (!(ent->flags & ESP_CMD_FLAG_WRITE))
			flush_fifo = 1;
	}

	if (flush_fifo)
		esp_flush_fifo(esp);

	return bytes_sent;
}