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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_dict_set_timestamp (int /*<<< orphan*/ **,char*,int) ; 

__attribute__((used)) static void mov_metadata_creation_time(AVDictionary **metadata, int64_t time, void *logctx)
{
    if (time) {
        if(time >= 2082844800)
            time -= 2082844800;  /* seconds between 1904-01-01 and Epoch */

        if ((int64_t)(time * 1000000ULL) / 1000000 != time) {
            av_log(logctx, AV_LOG_DEBUG, "creation_time is not representable\n");
            return;
        }

        avpriv_dict_set_timestamp(metadata, "creation_time", time * 1000000);
    }
}