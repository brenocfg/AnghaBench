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
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  import_10_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_audio_0_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_deint_0_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_denoise_0_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_detel_0_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_pic_0_0_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_video_0_0_0 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void import_0_0_0(hb_value_t *preset)
{
    import_video_0_0_0(preset);
    import_pic_0_0_0(preset);
    import_audio_0_0_0(preset);
    import_deint_0_0_0(preset);
    import_detel_0_0_0(preset);
    import_denoise_0_0_0(preset);

    // Import next...
    import_10_0_0(preset);
}