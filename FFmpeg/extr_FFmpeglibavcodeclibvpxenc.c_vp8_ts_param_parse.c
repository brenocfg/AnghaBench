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
struct vpx_codec_enc_cfg {int /*<<< orphan*/  ts_layer_id; void* ts_periodicity; int /*<<< orphan*/  ts_rate_decimator; int /*<<< orphan*/  ts_target_bitrate; void* ts_number_layers; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPX_TS_MAX_LAYERS ; 
 int /*<<< orphan*/  VPX_TS_MAX_PERIODICITY ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 void* strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  vp8_ts_parse_int_array (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vp8_ts_param_parse(struct vpx_codec_enc_cfg *enccfg, char *key, char *value)
{
    size_t value_len = strlen(value);

    if (!value_len)
        return -1;

    if (!strcmp(key, "ts_number_layers"))
        enccfg->ts_number_layers = strtoul(value, &value, 10);
    else if (!strcmp(key, "ts_target_bitrate"))
        vp8_ts_parse_int_array(enccfg->ts_target_bitrate, value, value_len, VPX_TS_MAX_LAYERS);
    else if (!strcmp(key, "ts_rate_decimator"))
      vp8_ts_parse_int_array(enccfg->ts_rate_decimator, value, value_len, VPX_TS_MAX_LAYERS);
    else if (!strcmp(key, "ts_periodicity"))
        enccfg->ts_periodicity = strtoul(value, &value, 10);
    else if (!strcmp(key, "ts_layer_id"))
        vp8_ts_parse_int_array(enccfg->ts_layer_id, value, value_len, VPX_TS_MAX_PERIODICITY);

    return 0;
}