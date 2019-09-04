#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  metadata; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * f; } ;
typedef  int /*<<< orphan*/  ModPlugFile ;
typedef  TYPE_1__ ModPlugContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_META_MULTIPLE_ENTRIES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* ModPlug_GetMessage (int /*<<< orphan*/ *) ; 
 char* ModPlug_GetName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ModPlug_InstrumentName ; 
 unsigned int ModPlug_NumChannels (int /*<<< orphan*/ *) ; 
 unsigned int ModPlug_NumInstruments (int /*<<< orphan*/ *) ; 
 unsigned int ModPlug_NumPatterns (int /*<<< orphan*/ *) ; 
 unsigned int ModPlug_NumSamples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ModPlug_SampleName ; 
 char* av_asprintf (char*,unsigned int,char*,unsigned int,char*) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instrument ; 
 int /*<<< orphan*/  sample ; 

__attribute__((used)) static int modplug_load_metadata(AVFormatContext *s)
{
    ModPlugContext *modplug = s->priv_data;
    ModPlugFile *f = modplug->f;
    char *extra;
    const char *name = ModPlug_GetName(f);
    const char *msg  = ModPlug_GetMessage(f);

    unsigned n_instruments = ModPlug_NumInstruments(f);
    unsigned n_samples     = ModPlug_NumSamples(f);
    unsigned n_patterns    = ModPlug_NumPatterns(f);
    unsigned n_channels    = ModPlug_NumChannels(f);

    if (name && *name) av_dict_set(&s->metadata, "name",    name, 0);
    if (msg  && *msg)  av_dict_set(&s->metadata, "message", msg,  0);

    extra = av_asprintf("%u pattern%s, %u channel%s",
                        n_patterns, n_patterns > 1 ? "s" : "",
                        n_channels, n_channels > 1 ? "s" : "");
    if (!extra)
        return AVERROR(ENOMEM);
    av_dict_set(&s->metadata, "extra info", extra, AV_DICT_DONT_STRDUP_VAL);

    ADD_META_MULTIPLE_ENTRIES(instrument, ModPlug_InstrumentName);
    ADD_META_MULTIPLE_ENTRIES(sample,     ModPlug_SampleName);

    return 0;
}