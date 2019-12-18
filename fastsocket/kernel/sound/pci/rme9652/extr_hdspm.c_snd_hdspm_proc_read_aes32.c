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
struct snd_info_entry {struct hdspm* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct hdspm {int control_register; int /*<<< orphan*/  system_sample_rate; scalar_t__ precise_ptr; scalar_t__ period_bytes; int /*<<< orphan*/  irq_count; scalar_t__ iobase; int /*<<< orphan*/  port; int /*<<< orphan*/  irq; int /*<<< orphan*/  firmware_rev; TYPE_1__* card; int /*<<< orphan*/  card_name; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
#define  HDSPM_AES32_AUTOSYNC_FROM_AES1 147 
#define  HDSPM_AES32_AUTOSYNC_FROM_AES2 146 
#define  HDSPM_AES32_AUTOSYNC_FROM_AES3 145 
#define  HDSPM_AES32_AUTOSYNC_FROM_AES4 144 
#define  HDSPM_AES32_AUTOSYNC_FROM_AES5 143 
#define  HDSPM_AES32_AUTOSYNC_FROM_AES6 142 
#define  HDSPM_AES32_AUTOSYNC_FROM_AES7 141 
#define  HDSPM_AES32_AUTOSYNC_FROM_AES8 140 
#define  HDSPM_AES32_AUTOSYNC_FROM_NONE 139 
#define  HDSPM_AES32_AUTOSYNC_FROM_WORD 138 
 unsigned int HDSPM_AES32_wcFreq_bit ; 
 unsigned int HDSPM_AES32_wcLock ; 
 unsigned int HDSPM_BufferID ; 
 unsigned int HDSPM_BufferPositionMask ; 
#define  HDSPM_CLOCK_SOURCE_AUTOSYNC 137 
#define  HDSPM_CLOCK_SOURCE_INTERNAL_128KHZ 136 
#define  HDSPM_CLOCK_SOURCE_INTERNAL_176_4KHZ 135 
#define  HDSPM_CLOCK_SOURCE_INTERNAL_192KHZ 134 
#define  HDSPM_CLOCK_SOURCE_INTERNAL_32KHZ 133 
#define  HDSPM_CLOCK_SOURCE_INTERNAL_44_1KHZ 132 
#define  HDSPM_CLOCK_SOURCE_INTERNAL_48KHZ 131 
#define  HDSPM_CLOCK_SOURCE_INTERNAL_64KHZ 130 
#define  HDSPM_CLOCK_SOURCE_INTERNAL_88_2KHZ 129 
#define  HDSPM_CLOCK_SOURCE_INTERNAL_96KHZ 128 
 int HDSPM_ClockModeMaster ; 
 int HDSPM_DS_DoubleWire ; 
 int HDSPM_Dolby ; 
 int HDSPM_Emphasis ; 
 int HDSPM_LatencyMask ; 
 int HDSPM_LineOut ; 
 int HDSPM_LockAES ; 
 int HDSPM_QS_DoubleWire ; 
 int HDSPM_QS_QuadWire ; 
 unsigned int HDSPM_audioIRQPending ; 
 int /*<<< orphan*/  HDSPM_bit2freq (unsigned int) ; 
 int HDSPM_clr_tms ; 
 unsigned int HDSPM_midi0IRQPending ; 
 unsigned int HDSPM_midi1IRQPending ; 
 int /*<<< orphan*/  HDSPM_midiStatusIn0 ; 
 int /*<<< orphan*/  HDSPM_midiStatusIn1 ; 
 int /*<<< orphan*/  HDSPM_midiStatusOut0 ; 
 int /*<<< orphan*/  HDSPM_midiStatusOut1 ; 
 int /*<<< orphan*/  HDSPM_statusRegister ; 
 int /*<<< orphan*/  HDSPM_statusRegister2 ; 
 int /*<<< orphan*/  HDSPM_timecodeRegister ; 
 int hdspm_autosync_ref (struct hdspm*) ; 
 int hdspm_clock_source (struct hdspm*) ; 
 int hdspm_decode_latency (int) ; 
 scalar_t__ hdspm_hw_pointer (struct hdspm*) ; 
 int hdspm_pref_sync_ref (struct hdspm*) ; 
 int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void
snd_hdspm_proc_read_aes32(struct snd_info_entry * entry,
			  struct snd_info_buffer *buffer)
{
	struct hdspm *hdspm = entry->private_data;
	unsigned int status;
	unsigned int status2;
	unsigned int timecode;
	int pref_syncref;
	char *autosync_ref;
	char *system_clock_mode;
	char *clock_source;
	int x;

	status = hdspm_read(hdspm, HDSPM_statusRegister);
	status2 = hdspm_read(hdspm, HDSPM_statusRegister2);
	timecode = hdspm_read(hdspm, HDSPM_timecodeRegister);

	snd_iprintf(buffer, "%s (Card #%d) Rev.%x\n",
		    hdspm->card_name, hdspm->card->number + 1,
		    hdspm->firmware_rev);

	snd_iprintf(buffer, "IRQ: %d Registers bus: 0x%lx VM: 0x%lx\n",
		    hdspm->irq, hdspm->port, (unsigned long)hdspm->iobase);

	snd_iprintf(buffer, "--- System ---\n");

	snd_iprintf(buffer,
		    "IRQ Pending: Audio=%d, MIDI0=%d, MIDI1=%d, IRQcount=%d\n",
		    status & HDSPM_audioIRQPending,
		    (status & HDSPM_midi0IRQPending) ? 1 : 0,
		    (status & HDSPM_midi1IRQPending) ? 1 : 0,
		    hdspm->irq_count);
	snd_iprintf(buffer,
		    "HW pointer: id = %d, rawptr = %d (%d->%d) "
		    "estimated= %ld (bytes)\n",
		    ((status & HDSPM_BufferID) ? 1 : 0),
		    (status & HDSPM_BufferPositionMask),
		    (status & HDSPM_BufferPositionMask) %
		    (2 * (int)hdspm->period_bytes),
		    ((status & HDSPM_BufferPositionMask) - 64) %
		    (2 * (int)hdspm->period_bytes),
		    (long) hdspm_hw_pointer(hdspm) * 4);

	snd_iprintf(buffer,
		    "MIDI FIFO: Out1=0x%x, Out2=0x%x, In1=0x%x, In2=0x%x \n",
		    hdspm_read(hdspm, HDSPM_midiStatusOut0) & 0xFF,
		    hdspm_read(hdspm, HDSPM_midiStatusOut1) & 0xFF,
		    hdspm_read(hdspm, HDSPM_midiStatusIn0) & 0xFF,
		    hdspm_read(hdspm, HDSPM_midiStatusIn1) & 0xFF);
	snd_iprintf(buffer,
		    "Register: ctrl1=0x%x, status1=0x%x, status2=0x%x, "
		    "timecode=0x%x\n",
		    hdspm->control_register,
		    status, status2, timecode);

	snd_iprintf(buffer, "--- Settings ---\n");

	x = 1 << (6 + hdspm_decode_latency(hdspm->control_register &
					   HDSPM_LatencyMask));

	snd_iprintf(buffer,
		    "Size (Latency): %d samples (2 periods of %lu bytes)\n",
		    x, (unsigned long) hdspm->period_bytes);

	snd_iprintf(buffer, "Line out: %s,   Precise Pointer: %s\n",
		    (hdspm->
		     control_register & HDSPM_LineOut) ? "on " : "off",
		    (hdspm->precise_ptr) ? "on" : "off");

	snd_iprintf(buffer,
		    "ClearTrackMarker %s, Emphasis %s, Dolby %s\n",
		    (hdspm->
		     control_register & HDSPM_clr_tms) ? "on" : "off",
		    (hdspm->
		     control_register & HDSPM_Emphasis) ? "on" : "off",
		    (hdspm->
		     control_register & HDSPM_Dolby) ? "on" : "off");

	switch (hdspm_clock_source(hdspm)) {
	case HDSPM_CLOCK_SOURCE_AUTOSYNC:
		clock_source = "AutoSync";
		break;
	case HDSPM_CLOCK_SOURCE_INTERNAL_32KHZ:
		clock_source = "Internal 32 kHz";
		break;
	case HDSPM_CLOCK_SOURCE_INTERNAL_44_1KHZ:
		clock_source = "Internal 44.1 kHz";
		break;
	case HDSPM_CLOCK_SOURCE_INTERNAL_48KHZ:
		clock_source = "Internal 48 kHz";
		break;
	case HDSPM_CLOCK_SOURCE_INTERNAL_64KHZ:
		clock_source = "Internal 64 kHz";
		break;
	case HDSPM_CLOCK_SOURCE_INTERNAL_88_2KHZ:
		clock_source = "Internal 88.2 kHz";
		break;
	case HDSPM_CLOCK_SOURCE_INTERNAL_96KHZ:
		clock_source = "Internal 96 kHz";
		break;
	case HDSPM_CLOCK_SOURCE_INTERNAL_128KHZ:
		clock_source = "Internal 128 kHz";
		break;
	case HDSPM_CLOCK_SOURCE_INTERNAL_176_4KHZ:
		clock_source = "Internal 176.4 kHz";
		break;
	case HDSPM_CLOCK_SOURCE_INTERNAL_192KHZ:
		clock_source = "Internal 192 kHz";
		break;
	default:
		clock_source = "Error";
	}
	snd_iprintf(buffer, "Sample Clock Source: %s\n", clock_source);
	if (!(hdspm->control_register & HDSPM_ClockModeMaster))
		system_clock_mode = "Slave";
	else
		system_clock_mode = "Master";
	snd_iprintf(buffer, "System Clock Mode: %s\n", system_clock_mode);

	pref_syncref = hdspm_pref_sync_ref(hdspm);
	if (pref_syncref == 0)
		snd_iprintf(buffer, "Preferred Sync Reference: Word Clock\n");
	else
		snd_iprintf(buffer, "Preferred Sync Reference: AES%d\n",
				pref_syncref);

	snd_iprintf(buffer, "System Clock Frequency: %d\n",
		    hdspm->system_sample_rate);

	snd_iprintf(buffer, "Double speed: %s\n",
			hdspm->control_register & HDSPM_DS_DoubleWire?
			"Double wire" : "Single wire");
	snd_iprintf(buffer, "Quad speed: %s\n",
			hdspm->control_register & HDSPM_QS_DoubleWire?
			"Double wire" :
			hdspm->control_register & HDSPM_QS_QuadWire?
			"Quad wire" : "Single wire");

	snd_iprintf(buffer, "--- Status:\n");

	snd_iprintf(buffer, "Word: %s  Frequency: %d\n",
		    (status & HDSPM_AES32_wcLock)? "Sync   " : "No Lock",
		    HDSPM_bit2freq((status >> HDSPM_AES32_wcFreq_bit) & 0xF));

	for (x = 0; x < 8; x++) {
		snd_iprintf(buffer, "AES%d: %s  Frequency: %d\n",
			    x+1,
			    (status2 & (HDSPM_LockAES >> x)) ?
			    "Sync   ": "No Lock",
			    HDSPM_bit2freq((timecode >> (4*x)) & 0xF));
	}

	switch (hdspm_autosync_ref(hdspm)) {
	case HDSPM_AES32_AUTOSYNC_FROM_NONE: autosync_ref="None"; break;
	case HDSPM_AES32_AUTOSYNC_FROM_WORD: autosync_ref="Word Clock"; break;
	case HDSPM_AES32_AUTOSYNC_FROM_AES1: autosync_ref="AES1"; break;
	case HDSPM_AES32_AUTOSYNC_FROM_AES2: autosync_ref="AES2"; break;
	case HDSPM_AES32_AUTOSYNC_FROM_AES3: autosync_ref="AES3"; break;
	case HDSPM_AES32_AUTOSYNC_FROM_AES4: autosync_ref="AES4"; break;
	case HDSPM_AES32_AUTOSYNC_FROM_AES5: autosync_ref="AES5"; break;
	case HDSPM_AES32_AUTOSYNC_FROM_AES6: autosync_ref="AES6"; break;
	case HDSPM_AES32_AUTOSYNC_FROM_AES7: autosync_ref="AES7"; break;
	case HDSPM_AES32_AUTOSYNC_FROM_AES8: autosync_ref="AES8"; break;
	default: autosync_ref = "---"; break;
	}
	snd_iprintf(buffer, "AutoSync ref = %s\n", autosync_ref);

	snd_iprintf(buffer, "\n");
}