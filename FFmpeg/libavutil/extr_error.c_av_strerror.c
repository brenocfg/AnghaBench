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
struct error_entry {int num; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVUNERROR (int) ; 
 int FF_ARRAY_ELEMS (struct error_entry*) ; 
 int /*<<< orphan*/  av_strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 struct error_entry* error_entries ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 
 int /*<<< orphan*/  strerror_r (int /*<<< orphan*/ ,char*,size_t) ; 

int av_strerror(int errnum, char *errbuf, size_t errbuf_size)
{
    int ret = 0, i;
    const struct error_entry *entry = NULL;

    for (i = 0; i < FF_ARRAY_ELEMS(error_entries); i++) {
        if (errnum == error_entries[i].num) {
            entry = &error_entries[i];
            break;
        }
    }
    if (entry) {
        av_strlcpy(errbuf, entry->str, errbuf_size);
    } else {
#if HAVE_STRERROR_R
        ret = AVERROR(strerror_r(AVUNERROR(errnum), errbuf, errbuf_size));
#else
        ret = -1;
#endif
        if (ret < 0)
            snprintf(errbuf, errbuf_size, "Error number %d occurred", errnum);
    }

    return ret;
}