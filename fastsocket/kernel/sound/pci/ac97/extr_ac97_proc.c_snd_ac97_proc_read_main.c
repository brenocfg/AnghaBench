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
struct snd_info_buffer {int dummy; } ;
struct snd_ac97 {int id; int scaps; unsigned short subsystem_vendor; unsigned short subsystem_device; unsigned short flags; unsigned short ext_id; unsigned short caps; int* regs; int /*<<< orphan*/  num; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 unsigned short AC97_ALC650_CC_MASK ; 
 unsigned short AC97_ALC650_CC_SHIFT ; 
 size_t AC97_ALC650_CLOCK ; 
 unsigned short AC97_ALC650_CLOCK_ACCURACY ; 
 unsigned short AC97_ALC650_CLOCK_LOCK ; 
 unsigned short AC97_ALC650_CLOCK_SHIFT ; 
 unsigned short AC97_ALC650_COPY ; 
 unsigned short AC97_ALC650_L ; 
 unsigned short AC97_ALC650_NAUDIO ; 
 unsigned short AC97_ALC650_PRE ; 
 unsigned short AC97_ALC650_PRO ; 
 size_t AC97_ALC650_SPDIF_INPUT_STATUS1 ; 
 size_t AC97_ALC650_SPDIF_INPUT_STATUS2 ; 
 unsigned short AC97_ALC650_SPSR_MASK ; 
 unsigned short AC97_ALC650_SPSR_SHIFT ; 
 unsigned short AC97_ALC650_V ; 
 unsigned short AC97_BC_16BIT_ADC ; 
 unsigned short AC97_BC_16BIT_DAC ; 
 unsigned short AC97_BC_18BIT_ADC ; 
 unsigned short AC97_BC_18BIT_DAC ; 
 unsigned short AC97_BC_20BIT_ADC ; 
 unsigned short AC97_BC_20BIT_DAC ; 
 unsigned short AC97_BC_ADC_MASK ; 
 unsigned short AC97_BC_BASS_TREBLE ; 
 unsigned short AC97_BC_DAC_MASK ; 
 unsigned short AC97_BC_DEDICATED_MIC ; 
 unsigned short AC97_BC_HEADPHONE ; 
 unsigned short AC97_BC_LOUDNESS ; 
 unsigned short AC97_BC_RESERVED1 ; 
 unsigned short AC97_BC_SIM_STEREO ; 
 size_t AC97_CODEC_CLASS_REV ; 
 size_t AC97_CSR_SPDIF ; 
 int AC97_CS_SPDIF ; 
 unsigned short AC97_EA_CDAC ; 
 unsigned short AC97_EA_DRA ; 
 unsigned short AC97_EA_LDAC ; 
 unsigned short AC97_EA_MDAC ; 
 unsigned short AC97_EA_PRI ; 
 unsigned short AC97_EA_PRJ ; 
 unsigned short AC97_EA_PRK ; 
 unsigned short AC97_EA_PRL ; 
 unsigned short AC97_EA_SDAC ; 
 unsigned short AC97_EA_SPCV ; 
 unsigned short AC97_EA_SPDIF ; 
 unsigned short AC97_EA_SPSA_SLOT_MASK ; 
 unsigned short AC97_EA_SPSA_SLOT_SHIFT ; 
 unsigned short AC97_EA_VRA ; 
 unsigned short AC97_EA_VRM ; 
 unsigned short AC97_EI_ADDR_MASK ; 
 unsigned short AC97_EI_ADDR_SHIFT ; 
 unsigned short AC97_EI_AMAP ; 
 unsigned short AC97_EI_CDAC ; 
 unsigned short AC97_EI_DACS_SLOT_MASK ; 
 unsigned short AC97_EI_DACS_SLOT_SHIFT ; 
 int AC97_EI_DRA ; 
 unsigned short AC97_EI_LDAC ; 
 unsigned short AC97_EI_REV_23 ; 
 unsigned short AC97_EI_REV_MASK ; 
 unsigned short AC97_EI_REV_SHIFT ; 
 unsigned short AC97_EI_SDAC ; 
 unsigned short AC97_EI_SPDIF ; 
 unsigned short AC97_EI_VRA ; 
 unsigned short AC97_EI_VRM ; 
 size_t AC97_EXTENDED_ID ; 
 size_t AC97_EXTENDED_MID ; 
 size_t AC97_EXTENDED_MSTATUS ; 
 size_t AC97_EXTENDED_STATUS ; 
 size_t AC97_GENERAL_PURPOSE ; 
 size_t AC97_HANDSET_RATE ; 
 int AC97_ID_YMF743 ; 
 size_t AC97_INT_PAGING ; 
 size_t AC97_LINE1_RATE ; 
 size_t AC97_LINE2_RATE ; 
 unsigned short AC97_MEA_ADC1 ; 
 unsigned short AC97_MEA_ADC2 ; 
 unsigned short AC97_MEA_DAC1 ; 
 unsigned short AC97_MEA_DAC2 ; 
 unsigned short AC97_MEA_GPIO ; 
 unsigned short AC97_MEA_HADC ; 
 unsigned short AC97_MEA_HDAC ; 
 unsigned short AC97_MEA_MREF ; 
 unsigned short AC97_MEA_PRA ; 
 unsigned short AC97_MEA_PRB ; 
 unsigned short AC97_MEA_PRC ; 
 unsigned short AC97_MEA_PRD ; 
 unsigned short AC97_MEA_PRE ; 
 unsigned short AC97_MEA_PRF ; 
 unsigned short AC97_MEA_PRG ; 
 unsigned short AC97_MEA_PRH ; 
 unsigned short AC97_MEI_ADDR_MASK ; 
 unsigned short AC97_MEI_ADDR_SHIFT ; 
 unsigned short AC97_MEI_CID1 ; 
 unsigned short AC97_MEI_CID2 ; 
 unsigned short AC97_MEI_HANDSET ; 
 unsigned short AC97_MEI_LINE1 ; 
 unsigned short AC97_MEI_LINE2 ; 
 size_t AC97_MIC ; 
 unsigned short AC97_PAGE_1 ; 
 unsigned short AC97_PAGE_MASK ; 
 size_t AC97_PCI_SID ; 
 size_t AC97_PCI_SVID ; 
 size_t AC97_PCM_FRONT_DAC_RATE ; 
 size_t AC97_PCM_LFE_DAC_RATE ; 
 size_t AC97_PCM_LR_ADC_RATE ; 
 size_t AC97_PCM_MIC_ADC_RATE ; 
 size_t AC97_PCM_SURR_DAC_RATE ; 
 int AC97_SCAP_AUDIO ; 
 unsigned short AC97_SC_CC_MASK ; 
 unsigned short AC97_SC_CC_SHIFT ; 
 unsigned short AC97_SC_COPY ; 
 unsigned short AC97_SC_DRS ; 
 unsigned short AC97_SC_L ; 
 unsigned short AC97_SC_NAUDIO ; 
 unsigned short AC97_SC_PRE ; 
 unsigned short AC97_SC_PRO ; 
 unsigned short AC97_SC_SPSR_MASK ; 
 unsigned short AC97_SC_SPSR_SHIFT ; 
 unsigned short AC97_SC_V ; 
 size_t AC97_SPDIF ; 
 size_t AC97_YMF7X3_DIT_CTRL ; 
 int /*<<< orphan*/  snd_ac97_get_name (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_proc_read_functions (struct snd_ac97*,struct snd_info_buffer*) ; 
 int snd_ac97_read (struct snd_ac97*,size_t) ; 
 unsigned short* snd_ac97_stereo_enhancements ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,size_t,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void snd_ac97_proc_read_main(struct snd_ac97 *ac97, struct snd_info_buffer *buffer, int subidx)
{
	char name[64];
	unsigned short val, tmp, ext, mext;
	static const char *spdif_slots[4] = { " SPDIF=3/4", " SPDIF=7/8", " SPDIF=6/9", " SPDIF=10/11" };
	static const char *spdif_rates[4] = { " Rate=44.1kHz", " Rate=res", " Rate=48kHz", " Rate=32kHz" };
	static const char *spdif_rates_cs4205[4] = { " Rate=48kHz", " Rate=44.1kHz", " Rate=res", " Rate=res" };
	static const char *double_rate_slots[4] = { "10/11", "7/8", "reserved", "reserved" };

	snd_ac97_get_name(NULL, ac97->id, name, 0);
	snd_iprintf(buffer, "%d-%d/%d: %s\n\n", ac97->addr, ac97->num, subidx, name);

	if ((ac97->scaps & AC97_SCAP_AUDIO) == 0)
		goto __modem;

        snd_iprintf(buffer, "PCI Subsys Vendor: 0x%04x\n",
	            ac97->subsystem_vendor);
        snd_iprintf(buffer, "PCI Subsys Device: 0x%04x\n\n",
                    ac97->subsystem_device);

	snd_iprintf(buffer, "Flags: %x\n", ac97->flags);

	if ((ac97->ext_id & AC97_EI_REV_MASK) >= AC97_EI_REV_23) {
		val = snd_ac97_read(ac97, AC97_INT_PAGING);
		snd_ac97_update_bits(ac97, AC97_INT_PAGING,
				     AC97_PAGE_MASK, AC97_PAGE_1);
		tmp = snd_ac97_read(ac97, AC97_CODEC_CLASS_REV);
		snd_iprintf(buffer, "Revision         : 0x%02x\n", tmp & 0xff);
		snd_iprintf(buffer, "Compat. Class    : 0x%02x\n", (tmp >> 8) & 0x1f);
		snd_iprintf(buffer, "Subsys. Vendor ID: 0x%04x\n",
			    snd_ac97_read(ac97, AC97_PCI_SVID));
		snd_iprintf(buffer, "Subsys. ID       : 0x%04x\n\n",
			    snd_ac97_read(ac97, AC97_PCI_SID));
		snd_ac97_update_bits(ac97, AC97_INT_PAGING,
				     AC97_PAGE_MASK, val & AC97_PAGE_MASK);
	}

	// val = snd_ac97_read(ac97, AC97_RESET);
	val = ac97->caps;
	snd_iprintf(buffer, "Capabilities     :%s%s%s%s%s%s\n",
	    	    val & AC97_BC_DEDICATED_MIC ? " -dedicated MIC PCM IN channel-" : "",
		    val & AC97_BC_RESERVED1 ? " -reserved1-" : "",
		    val & AC97_BC_BASS_TREBLE ? " -bass & treble-" : "",
		    val & AC97_BC_SIM_STEREO ? " -simulated stereo-" : "",
		    val & AC97_BC_HEADPHONE ? " -headphone out-" : "",
		    val & AC97_BC_LOUDNESS ? " -loudness-" : "");
	tmp = ac97->caps & AC97_BC_DAC_MASK;
	snd_iprintf(buffer, "DAC resolution   : %s%s%s%s\n",
		    tmp == AC97_BC_16BIT_DAC ? "16-bit" : "",
		    tmp == AC97_BC_18BIT_DAC ? "18-bit" : "",
		    tmp == AC97_BC_20BIT_DAC ? "20-bit" : "",
		    tmp == AC97_BC_DAC_MASK ? "???" : "");
	tmp = ac97->caps & AC97_BC_ADC_MASK;
	snd_iprintf(buffer, "ADC resolution   : %s%s%s%s\n",
		    tmp == AC97_BC_16BIT_ADC ? "16-bit" : "",
		    tmp == AC97_BC_18BIT_ADC ? "18-bit" : "",
		    tmp == AC97_BC_20BIT_ADC ? "20-bit" : "",
		    tmp == AC97_BC_ADC_MASK ? "???" : "");
	snd_iprintf(buffer, "3D enhancement   : %s\n",
		snd_ac97_stereo_enhancements[(val >> 10) & 0x1f]);
	snd_iprintf(buffer, "\nCurrent setup\n");
	val = snd_ac97_read(ac97, AC97_MIC);
	snd_iprintf(buffer, "Mic gain         : %s [%s]\n", val & 0x0040 ? "+20dB" : "+0dB", ac97->regs[AC97_MIC] & 0x0040 ? "+20dB" : "+0dB");
	val = snd_ac97_read(ac97, AC97_GENERAL_PURPOSE);
	snd_iprintf(buffer, "POP path         : %s 3D\n"
		    "Sim. stereo      : %s\n"
		    "3D enhancement   : %s\n"
		    "Loudness         : %s\n"
		    "Mono output      : %s\n"
		    "Mic select       : %s\n"
		    "ADC/DAC loopback : %s\n",
		    val & 0x8000 ? "post" : "pre",
		    val & 0x4000 ? "on" : "off",
		    val & 0x2000 ? "on" : "off",
		    val & 0x1000 ? "on" : "off",
		    val & 0x0200 ? "Mic" : "MIX",
		    val & 0x0100 ? "Mic2" : "Mic1",
		    val & 0x0080 ? "on" : "off");
	if (ac97->ext_id & AC97_EI_DRA)
		snd_iprintf(buffer, "Double rate slots: %s\n",
			    double_rate_slots[(val >> 10) & 3]);

	ext = snd_ac97_read(ac97, AC97_EXTENDED_ID);
	if (ext == 0)
		goto __modem;
		
	snd_iprintf(buffer, "Extended ID      : codec=%i rev=%i%s%s%s%s DSA=%i%s%s%s%s\n",
			(ext & AC97_EI_ADDR_MASK) >> AC97_EI_ADDR_SHIFT,
			(ext & AC97_EI_REV_MASK) >> AC97_EI_REV_SHIFT,
			ext & AC97_EI_AMAP ? " AMAP" : "",
			ext & AC97_EI_LDAC ? " LDAC" : "",
			ext & AC97_EI_SDAC ? " SDAC" : "",
			ext & AC97_EI_CDAC ? " CDAC" : "",
			(ext & AC97_EI_DACS_SLOT_MASK) >> AC97_EI_DACS_SLOT_SHIFT,
			ext & AC97_EI_VRM ? " VRM" : "",
			ext & AC97_EI_SPDIF ? " SPDIF" : "",
			ext & AC97_EI_DRA ? " DRA" : "",
			ext & AC97_EI_VRA ? " VRA" : "");
	val = snd_ac97_read(ac97, AC97_EXTENDED_STATUS);
	snd_iprintf(buffer, "Extended status  :%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
			val & AC97_EA_PRL ? " PRL" : "",
			val & AC97_EA_PRK ? " PRK" : "",
			val & AC97_EA_PRJ ? " PRJ" : "",
			val & AC97_EA_PRI ? " PRI" : "",
			val & AC97_EA_SPCV ? " SPCV" : "",
			val & AC97_EA_MDAC ? " MADC" : "",
			val & AC97_EA_LDAC ? " LDAC" : "",
			val & AC97_EA_SDAC ? " SDAC" : "",
			val & AC97_EA_CDAC ? " CDAC" : "",
			ext & AC97_EI_SPDIF ? spdif_slots[(val & AC97_EA_SPSA_SLOT_MASK) >> AC97_EA_SPSA_SLOT_SHIFT] : "",
			val & AC97_EA_VRM ? " VRM" : "",
			val & AC97_EA_SPDIF ? " SPDIF" : "",
			val & AC97_EA_DRA ? " DRA" : "",
			val & AC97_EA_VRA ? " VRA" : "");
	if (ext & AC97_EI_VRA) {	/* VRA */
		val = snd_ac97_read(ac97, AC97_PCM_FRONT_DAC_RATE);
		snd_iprintf(buffer, "PCM front DAC    : %iHz\n", val);
		if (ext & AC97_EI_SDAC) {
			val = snd_ac97_read(ac97, AC97_PCM_SURR_DAC_RATE);
			snd_iprintf(buffer, "PCM Surr DAC     : %iHz\n", val);
		}
		if (ext & AC97_EI_LDAC) {
			val = snd_ac97_read(ac97, AC97_PCM_LFE_DAC_RATE);
			snd_iprintf(buffer, "PCM LFE DAC      : %iHz\n", val);
		}
		val = snd_ac97_read(ac97, AC97_PCM_LR_ADC_RATE);
		snd_iprintf(buffer, "PCM ADC          : %iHz\n", val);
	}
	if (ext & AC97_EI_VRM) {
		val = snd_ac97_read(ac97, AC97_PCM_MIC_ADC_RATE);
		snd_iprintf(buffer, "PCM MIC ADC      : %iHz\n", val);
	}
	if ((ext & AC97_EI_SPDIF) || (ac97->flags & AC97_CS_SPDIF) ||
	    (ac97->id == AC97_ID_YMF743)) {
	        if (ac97->flags & AC97_CS_SPDIF)
			val = snd_ac97_read(ac97, AC97_CSR_SPDIF);
		else if (ac97->id == AC97_ID_YMF743) {
			val = snd_ac97_read(ac97, AC97_YMF7X3_DIT_CTRL);
			val = 0x2000 | (val & 0xff00) >> 4 | (val & 0x38) >> 2;
		} else
			val = snd_ac97_read(ac97, AC97_SPDIF);

		snd_iprintf(buffer, "SPDIF Control    :%s%s%s%s Category=0x%x Generation=%i%s%s%s\n",
			val & AC97_SC_PRO ? " PRO" : " Consumer",
			val & AC97_SC_NAUDIO ? " Non-audio" : " PCM",
			val & AC97_SC_COPY ? "" : " Copyright",
			val & AC97_SC_PRE ? " Preemph50/15" : "",
			(val & AC97_SC_CC_MASK) >> AC97_SC_CC_SHIFT,
			(val & AC97_SC_L) >> 11,
			(ac97->flags & AC97_CS_SPDIF) ?
			    spdif_rates_cs4205[(val & AC97_SC_SPSR_MASK) >> AC97_SC_SPSR_SHIFT] :
			    spdif_rates[(val & AC97_SC_SPSR_MASK) >> AC97_SC_SPSR_SHIFT],
			(ac97->flags & AC97_CS_SPDIF) ?
			    (val & AC97_SC_DRS ? " Validity" : "") :
			    (val & AC97_SC_DRS ? " DRS" : ""),
			(ac97->flags & AC97_CS_SPDIF) ?
			    (val & AC97_SC_V ? " Enabled" : "") :
			    (val & AC97_SC_V ? " Validity" : ""));
		/* ALC650 specific*/
		if ((ac97->id & 0xfffffff0) == 0x414c4720 &&
		    (snd_ac97_read(ac97, AC97_ALC650_CLOCK) & 0x01)) {
			val = snd_ac97_read(ac97, AC97_ALC650_SPDIF_INPUT_STATUS2);
			if (val & AC97_ALC650_CLOCK_LOCK) {
				val = snd_ac97_read(ac97, AC97_ALC650_SPDIF_INPUT_STATUS1);
				snd_iprintf(buffer, "SPDIF In Status  :%s%s%s%s Category=0x%x Generation=%i",
					    val & AC97_ALC650_PRO ? " PRO" : " Consumer",
					    val & AC97_ALC650_NAUDIO ? " Non-audio" : " PCM",
					    val & AC97_ALC650_COPY ? "" : " Copyright",
					    val & AC97_ALC650_PRE ? " Preemph50/15" : "",
					    (val & AC97_ALC650_CC_MASK) >> AC97_ALC650_CC_SHIFT,
					    (val & AC97_ALC650_L) >> 15);
				val = snd_ac97_read(ac97, AC97_ALC650_SPDIF_INPUT_STATUS2);
				snd_iprintf(buffer, "%s Accuracy=%i%s%s\n",
					    spdif_rates[(val & AC97_ALC650_SPSR_MASK) >> AC97_ALC650_SPSR_SHIFT],
					    (val & AC97_ALC650_CLOCK_ACCURACY) >> AC97_ALC650_CLOCK_SHIFT,
					    (val & AC97_ALC650_CLOCK_LOCK ? " Locked" : " Unlocked"),
					    (val & AC97_ALC650_V ? " Validity?" : ""));
			} else {
				snd_iprintf(buffer, "SPDIF In Status  : Not Locked\n");
			}
		}
	}
	if ((ac97->ext_id & AC97_EI_REV_MASK) >= AC97_EI_REV_23) {
		val = snd_ac97_read(ac97, AC97_INT_PAGING);
		snd_ac97_update_bits(ac97, AC97_INT_PAGING,
				     AC97_PAGE_MASK, AC97_PAGE_1);
		snd_ac97_proc_read_functions(ac97, buffer);
		snd_ac97_update_bits(ac97, AC97_INT_PAGING,
				     AC97_PAGE_MASK, val & AC97_PAGE_MASK);
	}


      __modem:
	mext = snd_ac97_read(ac97, AC97_EXTENDED_MID);
	if (mext == 0)
		return;
	
	snd_iprintf(buffer, "Extended modem ID: codec=%i%s%s%s%s%s\n",
			(mext & AC97_MEI_ADDR_MASK) >> AC97_MEI_ADDR_SHIFT,
			mext & AC97_MEI_CID2 ? " CID2" : "",
			mext & AC97_MEI_CID1 ? " CID1" : "",
			mext & AC97_MEI_HANDSET ? " HSET" : "",
			mext & AC97_MEI_LINE2 ? " LIN2" : "",
			mext & AC97_MEI_LINE1 ? " LIN1" : "");
	val = snd_ac97_read(ac97, AC97_EXTENDED_MSTATUS);
	snd_iprintf(buffer, "Modem status     :%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
			val & AC97_MEA_GPIO ? " GPIO" : "",
			val & AC97_MEA_MREF ? " MREF" : "",
			val & AC97_MEA_ADC1 ? " ADC1" : "",
			val & AC97_MEA_DAC1 ? " DAC1" : "",
			val & AC97_MEA_ADC2 ? " ADC2" : "",
			val & AC97_MEA_DAC2 ? " DAC2" : "",
			val & AC97_MEA_HADC ? " HADC" : "",
			val & AC97_MEA_HDAC ? " HDAC" : "",
			val & AC97_MEA_PRA ? " PRA(GPIO)" : "",
			val & AC97_MEA_PRB ? " PRB(res)" : "",
			val & AC97_MEA_PRC ? " PRC(ADC1)" : "",
			val & AC97_MEA_PRD ? " PRD(DAC1)" : "",
			val & AC97_MEA_PRE ? " PRE(ADC2)" : "",
			val & AC97_MEA_PRF ? " PRF(DAC2)" : "",
			val & AC97_MEA_PRG ? " PRG(HADC)" : "",
			val & AC97_MEA_PRH ? " PRH(HDAC)" : "");
	if (mext & AC97_MEI_LINE1) {
		val = snd_ac97_read(ac97, AC97_LINE1_RATE);
		snd_iprintf(buffer, "Line1 rate       : %iHz\n", val);
	}
	if (mext & AC97_MEI_LINE2) {
		val = snd_ac97_read(ac97, AC97_LINE2_RATE);
		snd_iprintf(buffer, "Line2 rate       : %iHz\n", val);
	}
	if (mext & AC97_MEI_HANDSET) {
		val = snd_ac97_read(ac97, AC97_HANDSET_RATE);
		snd_iprintf(buffer, "Headset rate     : %iHz\n", val);
	}
}