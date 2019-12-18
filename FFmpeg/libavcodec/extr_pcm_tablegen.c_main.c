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

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ARRAY (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linear_to_alaw ; 
 int /*<<< orphan*/  linear_to_ulaw ; 
 int /*<<< orphan*/  linear_to_vidc ; 
 int /*<<< orphan*/  pcm_alaw_tableinit () ; 
 int /*<<< orphan*/  pcm_ulaw_tableinit () ; 
 int /*<<< orphan*/  pcm_vidc_tableinit () ; 
 int /*<<< orphan*/  uint8_t ; 
 int /*<<< orphan*/  write_fileheader () ; 

int main(void)
{
    pcm_alaw_tableinit();
    pcm_ulaw_tableinit();
    pcm_vidc_tableinit();

    write_fileheader();

    WRITE_ARRAY("static const", uint8_t, linear_to_alaw);
    WRITE_ARRAY("static const", uint8_t, linear_to_ulaw);
    WRITE_ARRAY("static const", uint8_t, linear_to_vidc);

    return 0;
}