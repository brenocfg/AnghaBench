#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int tags_mapped; int /*<<< orphan*/ *** che; int /*<<< orphan*/ *** tag_che_map; TYPE_2__* oc; int /*<<< orphan*/  warned_remapping_once; int /*<<< orphan*/  avctx; } ;
struct TYPE_7__ {int chan_config; int ps; scalar_t__ sbr; } ;
struct TYPE_8__ {TYPE_1__ m4ac; } ;
typedef  int /*<<< orphan*/  ChannelElement ;
typedef  TYPE_3__ AACContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int MAX_ELEM_ID ; 
 int /*<<< orphan*/  OC_TRIAL_FRAME ; 
 int TYPE_CPE ; 
 int TYPE_LFE ; 
 int TYPE_SCE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ output_configure (TYPE_3__*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  push_output_configuration (TYPE_3__*) ; 
 scalar_t__ set_default_channel_config (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int) ; 
 int /*<<< orphan*/ * tags_per_config ; 

__attribute__((used)) static ChannelElement *get_che(AACContext *ac, int type, int elem_id)
{
    /* For PCE based channel configurations map the channels solely based
     * on tags. */
    if (!ac->oc[1].m4ac.chan_config) {
        return ac->tag_che_map[type][elem_id];
    }
    // Allow single CPE stereo files to be signalled with mono configuration.
    if (!ac->tags_mapped && type == TYPE_CPE &&
        ac->oc[1].m4ac.chan_config == 1) {
        uint8_t layout_map[MAX_ELEM_ID*4][3];
        int layout_map_tags;
        push_output_configuration(ac);

        av_log(ac->avctx, AV_LOG_DEBUG, "mono with CPE\n");

        if (set_default_channel_config(ac->avctx, layout_map,
                                       &layout_map_tags, 2) < 0)
            return NULL;
        if (output_configure(ac, layout_map, layout_map_tags,
                             OC_TRIAL_FRAME, 1) < 0)
            return NULL;

        ac->oc[1].m4ac.chan_config = 2;
        ac->oc[1].m4ac.ps = 0;
    }
    // And vice-versa
    if (!ac->tags_mapped && type == TYPE_SCE &&
        ac->oc[1].m4ac.chan_config == 2) {
        uint8_t layout_map[MAX_ELEM_ID * 4][3];
        int layout_map_tags;
        push_output_configuration(ac);

        av_log(ac->avctx, AV_LOG_DEBUG, "stereo with SCE\n");

        if (set_default_channel_config(ac->avctx, layout_map,
                                       &layout_map_tags, 1) < 0)
            return NULL;
        if (output_configure(ac, layout_map, layout_map_tags,
                             OC_TRIAL_FRAME, 1) < 0)
            return NULL;

        ac->oc[1].m4ac.chan_config = 1;
        if (ac->oc[1].m4ac.sbr)
            ac->oc[1].m4ac.ps = -1;
    }
    /* For indexed channel configurations map the channels solely based
     * on position. */
    switch (ac->oc[1].m4ac.chan_config) {
    case 12:
    case 7:
        if (ac->tags_mapped == 3 && type == TYPE_CPE) {
            ac->tags_mapped++;
            return ac->tag_che_map[TYPE_CPE][elem_id] = ac->che[TYPE_CPE][2];
        }
    case 11:
        if (ac->tags_mapped == 2 &&
            ac->oc[1].m4ac.chan_config == 11 &&
            type == TYPE_SCE) {
            ac->tags_mapped++;
            return ac->tag_che_map[TYPE_SCE][elem_id] = ac->che[TYPE_SCE][1];
        }
    case 6:
        /* Some streams incorrectly code 5.1 audio as
         * SCE[0] CPE[0] CPE[1] SCE[1]
         * instead of
         * SCE[0] CPE[0] CPE[1] LFE[0].
         * If we seem to have encountered such a stream, transfer
         * the LFE[0] element to the SCE[1]'s mapping */
        if (ac->tags_mapped == tags_per_config[ac->oc[1].m4ac.chan_config] - 1 && (type == TYPE_LFE || type == TYPE_SCE)) {
            if (!ac->warned_remapping_once && (type != TYPE_LFE || elem_id != 0)) {
                av_log(ac->avctx, AV_LOG_WARNING,
                   "This stream seems to incorrectly report its last channel as %s[%d], mapping to LFE[0]\n",
                   type == TYPE_SCE ? "SCE" : "LFE", elem_id);
                ac->warned_remapping_once++;
            }
            ac->tags_mapped++;
            return ac->tag_che_map[type][elem_id] = ac->che[TYPE_LFE][0];
        }
    case 5:
        if (ac->tags_mapped == 2 && type == TYPE_CPE) {
            ac->tags_mapped++;
            return ac->tag_che_map[TYPE_CPE][elem_id] = ac->che[TYPE_CPE][1];
        }
    case 4:
        /* Some streams incorrectly code 4.0 audio as
         * SCE[0] CPE[0] LFE[0]
         * instead of
         * SCE[0] CPE[0] SCE[1].
         * If we seem to have encountered such a stream, transfer
         * the SCE[1] element to the LFE[0]'s mapping */
        if (ac->tags_mapped == tags_per_config[ac->oc[1].m4ac.chan_config] - 1 && (type == TYPE_LFE || type == TYPE_SCE)) {
            if (!ac->warned_remapping_once && (type != TYPE_SCE || elem_id != 1)) {
                av_log(ac->avctx, AV_LOG_WARNING,
                   "This stream seems to incorrectly report its last channel as %s[%d], mapping to SCE[1]\n",
                   type == TYPE_SCE ? "SCE" : "LFE", elem_id);
                ac->warned_remapping_once++;
            }
            ac->tags_mapped++;
            return ac->tag_che_map[type][elem_id] = ac->che[TYPE_SCE][1];
        }
        if (ac->tags_mapped == 2 &&
            ac->oc[1].m4ac.chan_config == 4 &&
            type == TYPE_SCE) {
            ac->tags_mapped++;
            return ac->tag_che_map[TYPE_SCE][elem_id] = ac->che[TYPE_SCE][1];
        }
    case 3:
    case 2:
        if (ac->tags_mapped == (ac->oc[1].m4ac.chan_config != 2) &&
            type == TYPE_CPE) {
            ac->tags_mapped++;
            return ac->tag_che_map[TYPE_CPE][elem_id] = ac->che[TYPE_CPE][0];
        } else if (ac->oc[1].m4ac.chan_config == 2) {
            return NULL;
        }
    case 1:
        if (!ac->tags_mapped && type == TYPE_SCE) {
            ac->tags_mapped++;
            return ac->tag_che_map[TYPE_SCE][elem_id] = ac->che[TYPE_SCE][0];
        }
    default:
        return NULL;
    }
}