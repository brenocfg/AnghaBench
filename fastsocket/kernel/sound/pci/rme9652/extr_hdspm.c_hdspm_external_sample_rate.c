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
struct hdspm {scalar_t__ is_aes32; } ;

/* Variables and functions */
 int HDSPM_AES32_AUTOSYNC_FROM_AES1 ; 
 int HDSPM_AES32_AUTOSYNC_FROM_AES8 ; 
 int HDSPM_AES32_AUTOSYNC_FROM_WORD ; 
 unsigned int HDSPM_AES32_wcFreq_bit ; 
 unsigned int HDSPM_AES32_wcLock ; 
 int HDSPM_LockAES ; 
 unsigned int HDSPM_SelSyncRef0 ; 
 unsigned int HDSPM_SelSyncRefMask ; 
 unsigned int HDSPM_SelSyncRef_WORD ; 
 int HDSPM_bit2freq (unsigned int) ; 
#define  HDSPM_madiFreq128 142 
#define  HDSPM_madiFreq176_4 141 
#define  HDSPM_madiFreq192 140 
#define  HDSPM_madiFreq32 139 
#define  HDSPM_madiFreq44_1 138 
#define  HDSPM_madiFreq48 137 
#define  HDSPM_madiFreq64 136 
#define  HDSPM_madiFreq88_2 135 
#define  HDSPM_madiFreq96 134 
 unsigned int HDSPM_madiFreqMask ; 
 unsigned int HDSPM_madiLock ; 
 int /*<<< orphan*/  HDSPM_statusRegister ; 
 int /*<<< orphan*/  HDSPM_statusRegister2 ; 
 int /*<<< orphan*/  HDSPM_timecodeRegister ; 
#define  HDSPM_wcFreq32 133 
#define  HDSPM_wcFreq44_1 132 
#define  HDSPM_wcFreq48 131 
#define  HDSPM_wcFreq64 130 
#define  HDSPM_wcFreq88_2 129 
#define  HDSPM_wcFreq96 128 
 unsigned int HDSPM_wcFreqMask ; 
 unsigned int HDSPM_wcLock ; 
 int hdspm_autosync_ref (struct hdspm*) ; 
 unsigned int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdspm_external_sample_rate(struct hdspm *hdspm)
{
	if (hdspm->is_aes32) {
		unsigned int status2 = hdspm_read(hdspm, HDSPM_statusRegister2);
		unsigned int status = hdspm_read(hdspm, HDSPM_statusRegister);
		unsigned int timecode =
			hdspm_read(hdspm, HDSPM_timecodeRegister);

		int syncref = hdspm_autosync_ref(hdspm);

		if (syncref == HDSPM_AES32_AUTOSYNC_FROM_WORD &&
				status & HDSPM_AES32_wcLock)
			return HDSPM_bit2freq((status >> HDSPM_AES32_wcFreq_bit)
					      & 0xF);
		if (syncref >= HDSPM_AES32_AUTOSYNC_FROM_AES1 &&
			syncref <= HDSPM_AES32_AUTOSYNC_FROM_AES8 &&
			status2 & (HDSPM_LockAES >>
			          (syncref - HDSPM_AES32_AUTOSYNC_FROM_AES1)))
			return HDSPM_bit2freq((timecode >>
			  (4*(syncref-HDSPM_AES32_AUTOSYNC_FROM_AES1))) & 0xF);
		return 0;
	} else {
		unsigned int status2 = hdspm_read(hdspm, HDSPM_statusRegister2);
		unsigned int status = hdspm_read(hdspm, HDSPM_statusRegister);
		unsigned int rate_bits;
		int rate = 0;

		/* if wordclock has synced freq and wordclock is valid */
		if ((status2 & HDSPM_wcLock) != 0 &&
				(status & HDSPM_SelSyncRef0) == 0) {

			rate_bits = status2 & HDSPM_wcFreqMask;

			switch (rate_bits) {
			case HDSPM_wcFreq32:
				rate = 32000;
				break;
			case HDSPM_wcFreq44_1:
				rate = 44100;
				break;
			case HDSPM_wcFreq48:
				rate = 48000;
				break;
			case HDSPM_wcFreq64:
				rate = 64000;
				break;
			case HDSPM_wcFreq88_2:
				rate = 88200;
				break;
			case HDSPM_wcFreq96:
				rate = 96000;
				break;
				/* Quadspeed Bit missing ???? */
			default:
				rate = 0;
				break;
			}
		}

		/* if rate detected and Syncref is Word than have it,
		 * word has priority to MADI
		 */
		if (rate != 0 &&
	            (status2 & HDSPM_SelSyncRefMask) == HDSPM_SelSyncRef_WORD)
			return rate;

		/* maby a madi input (which is taken if sel sync is madi) */
		if (status & HDSPM_madiLock) {
			rate_bits = status & HDSPM_madiFreqMask;

			switch (rate_bits) {
			case HDSPM_madiFreq32:
				rate = 32000;
				break;
			case HDSPM_madiFreq44_1:
				rate = 44100;
				break;
			case HDSPM_madiFreq48:
				rate = 48000;
				break;
			case HDSPM_madiFreq64:
				rate = 64000;
				break;
			case HDSPM_madiFreq88_2:
				rate = 88200;
				break;
			case HDSPM_madiFreq96:
				rate = 96000;
				break;
			case HDSPM_madiFreq128:
				rate = 128000;
				break;
			case HDSPM_madiFreq176_4:
				rate = 176400;
				break;
			case HDSPM_madiFreq192:
				rate = 192000;
				break;
			default:
				rate = 0;
				break;
			}
		}
		return rate;
	}
}