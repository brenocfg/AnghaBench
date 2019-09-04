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
typedef  enum AVColorTransferCharacteristic { ____Placeholder_AVColorTransferCharacteristic } AVColorTransferCharacteristic ;
typedef  int /*<<< orphan*/  WriterContext ;

/* Variables and functions */
 int AVCOL_TRC_UNSPECIFIED ; 
 char* av_color_transfer_name (int) ; 
 int /*<<< orphan*/  print_str (char*,char const*) ; 
 int /*<<< orphan*/  print_str_opt (char*,char*) ; 

__attribute__((used)) static void print_color_trc(WriterContext *w, enum AVColorTransferCharacteristic color_trc)
{
    const char *val = av_color_transfer_name(color_trc);
    if (!val || color_trc == AVCOL_TRC_UNSPECIFIED) {
        print_str_opt("color_transfer", "unknown");
    } else {
        print_str("color_transfer", val);
    }
}