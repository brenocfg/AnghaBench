#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ filename; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int openmpt_is_extension_supported (char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (scalar_t__,char) ; 

__attribute__((used)) static int probe_openmpt_extension(AVProbeData *p)
{
    const char *ext;
    if (p->filename) {
        ext = strrchr(p->filename, '.');
        if (ext && strlen(ext + 1) > 0) {
            ext++;  /* skip '.' */
            if (openmpt_is_extension_supported(ext) == 1)
                return AVPROBE_SCORE_EXTENSION;
        }
    }
    return 0;
}