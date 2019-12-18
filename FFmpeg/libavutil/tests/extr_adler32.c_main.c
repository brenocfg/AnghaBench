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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int LEN ; 
 int /*<<< orphan*/  START_TIMER ; 
 int /*<<< orphan*/  STOP_TIMER (char*) ; 
 int av_adler32_update (int,int*,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  av_log_set_level (int /*<<< orphan*/ ) ; 
 int checksum ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int main(int argc, char **argv)
{
    int i;
    uint8_t data[LEN];

    av_log_set_level(AV_LOG_DEBUG);

    for (i = 0; i < LEN; i++)
        data[i] = ((i * i) >> 3) + 123 * i;

    if (argc > 1 && !strcmp(argv[1], "-t")) {
        for (i = 0; i < 1000; i++) {
            START_TIMER;
            checksum = av_adler32_update(1, data, LEN);
            STOP_TIMER("adler");
        }
    } else {
        checksum = av_adler32_update(1, data, LEN);
    }

    av_log(NULL, AV_LOG_DEBUG, "%X (expected 50E6E508)\n", checksum);
    return checksum == 0x50e6e508 ? 0 : 1;
}