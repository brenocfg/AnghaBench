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
typedef  int /*<<< orphan*/  VC2EncContext ;

/* Variables and functions */
 int /*<<< orphan*/  encode_aspect_ratio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_clean_area (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_color_spec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_frame_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_frame_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_sample_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_scan_format (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_signal_range (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void encode_source_params(VC2EncContext *s)
{
    encode_frame_size(s);
    encode_sample_fmt(s);
    encode_scan_format(s);
    encode_frame_rate(s);
    encode_aspect_ratio(s);
    encode_clean_area(s);
    encode_signal_range(s);
    encode_color_spec(s);
}