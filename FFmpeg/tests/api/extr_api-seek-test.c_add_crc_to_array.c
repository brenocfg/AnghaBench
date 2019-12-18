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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_realloc_f (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * crc_array ; 
 int number_of_elements ; 
 int /*<<< orphan*/ * pts_array ; 
 int size_of_array ; 

__attribute__((used)) static int add_crc_to_array(uint32_t crc, int64_t pts)
{
    if (size_of_array <= number_of_elements) {
        if (size_of_array == 0)
            size_of_array = 10;
        size_of_array *= 2;
        crc_array = av_realloc_f(crc_array, size_of_array, sizeof(uint32_t));
        pts_array = av_realloc_f(pts_array, size_of_array, sizeof(int64_t));
        if ((crc_array == NULL) || (pts_array == NULL)) {
            av_log(NULL, AV_LOG_ERROR, "Can't allocate array to store crcs\n");
            return AVERROR(ENOMEM);
        }
    }
    crc_array[number_of_elements] = crc;
    pts_array[number_of_elements] = pts;
    number_of_elements++;
    return 0;
}