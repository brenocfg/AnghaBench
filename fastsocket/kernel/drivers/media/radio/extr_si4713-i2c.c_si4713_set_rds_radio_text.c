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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  radio_text; } ;
struct si4713_device {int /*<<< orphan*/  mutex; TYPE_1__ rds_info; int /*<<< orphan*/  power_state; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RDS_RADIO_TEXT ; 
 int /*<<< orphan*/  RDS_BLOCK_CLEAR ; 
 int /*<<< orphan*/  RDS_BLOCK_LOAD ; 
 char RDS_CARRIAGE_RETURN ; 
 char RDS_RADIOTEXT_2A ; 
 int RDS_RADIOTEXT_BLK_SIZE ; 
 int RDS_RADIOTEXT_INDEX_MAX ; 
 int /*<<< orphan*/  compose_u16 (char,char) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si4713_tx_rds_buff (struct si4713_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si4713_set_rds_radio_text(struct si4713_device *sdev, char *rt)
{
	int rval = 0, i;
	u16 t_index = 0;
	u8 b_index = 0, cr_inserted = 0;
	s8 left;

	mutex_lock(&sdev->mutex);

	if (!sdev->power_state)
		goto copy;

	rval = si4713_tx_rds_buff(sdev, RDS_BLOCK_CLEAR, 0, 0, 0, &left);
	if (rval < 0)
		goto unlock;

	if (!strlen(rt))
		goto copy;

	do {
		/* RDS spec says that if the last block isn't used,
		 * then apply a carriage return
		 */
		if (t_index < (RDS_RADIOTEXT_INDEX_MAX *
			RDS_RADIOTEXT_BLK_SIZE)) {
			for (i = 0; i < RDS_RADIOTEXT_BLK_SIZE; i++) {
				if (!rt[t_index + i] || rt[t_index + i] ==
					RDS_CARRIAGE_RETURN) {
					rt[t_index + i] = RDS_CARRIAGE_RETURN;
					cr_inserted = 1;
					break;
				}
			}
		}

		rval = si4713_tx_rds_buff(sdev, RDS_BLOCK_LOAD,
				compose_u16(RDS_RADIOTEXT_2A, b_index++),
				compose_u16(rt[t_index], rt[t_index + 1]),
				compose_u16(rt[t_index + 2], rt[t_index + 3]),
				&left);
		if (rval < 0)
			goto unlock;

		t_index += RDS_RADIOTEXT_BLK_SIZE;

		if (cr_inserted)
			break;
	} while (left > 0);

copy:
	strncpy(sdev->rds_info.radio_text, rt, MAX_RDS_RADIO_TEXT);

unlock:
	mutex_unlock(&sdev->mutex);
	return rval;
}