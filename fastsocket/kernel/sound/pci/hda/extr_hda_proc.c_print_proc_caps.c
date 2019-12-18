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
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PAR_PROC_CAP ; 
 unsigned int AC_PCAP_BENIGN ; 
 unsigned int AC_PCAP_NUM_COEF ; 
 unsigned int AC_PCAP_NUM_COEF_SHIFT ; 
 unsigned int snd_hda_param_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void print_proc_caps(struct snd_info_buffer *buffer,
			    struct hda_codec *codec, hda_nid_t nid)
{
	unsigned int proc_caps = snd_hda_param_read(codec, nid,
						    AC_PAR_PROC_CAP);
	snd_iprintf(buffer, "  Processing caps: benign=%d, ncoeff=%d\n",
		    proc_caps & AC_PCAP_BENIGN,
		    (proc_caps & AC_PCAP_NUM_COEF) >> AC_PCAP_NUM_COEF_SHIFT);
}