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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  URLContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ff_amf_write_bool (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ff_amf_write_field_name (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  ff_amf_write_null (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_amf_write_number (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_amf_write_object_end (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_amf_write_object_start (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_amf_write_string (int /*<<< orphan*/ **,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strtod (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtmp_write_amf_data(URLContext *s, char *param, uint8_t **p)
{
    char *field, *value;
    char type;

    /* The type must be B for Boolean, N for number, S for string, O for
     * object, or Z for null. For Booleans the data must be either 0 or 1 for
     * FALSE or TRUE, respectively. Likewise for Objects the data must be
     * 0 or 1 to end or begin an object, respectively. Data items in subobjects
     * may be named, by prefixing the type with 'N' and specifying the name
     * before the value (ie. NB:myFlag:1). This option may be used multiple times
     * to construct arbitrary AMF sequences. */
    if (param[0] && param[1] == ':') {
        type = param[0];
        value = param + 2;
    } else if (param[0] == 'N' && param[1] && param[2] == ':') {
        type = param[1];
        field = param + 3;
        value = strchr(field, ':');
        if (!value)
            goto fail;
        *value = '\0';
        value++;

        ff_amf_write_field_name(p, field);
    } else {
        goto fail;
    }

    switch (type) {
    case 'B':
        ff_amf_write_bool(p, value[0] != '0');
        break;
    case 'S':
        ff_amf_write_string(p, value);
        break;
    case 'N':
        ff_amf_write_number(p, strtod(value, NULL));
        break;
    case 'Z':
        ff_amf_write_null(p);
        break;
    case 'O':
        if (value[0] != '0')
            ff_amf_write_object_start(p);
        else
            ff_amf_write_object_end(p);
        break;
    default:
        goto fail;
        break;
    }

    return 0;

fail:
    av_log(s, AV_LOG_ERROR, "Invalid AMF parameter: %s\n", param);
    return AVERROR(EINVAL);
}