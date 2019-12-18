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
typedef  enum XML_Status { ____Placeholder_XML_Status } XML_Status ;
typedef  enum XML_FeatureEnum { ____Placeholder_XML_FeatureEnum } XML_FeatureEnum ;
struct TYPE_3__ {scalar_t__ feature; long value; } ;
typedef  TYPE_1__ XML_Feature ;

/* Variables and functions */
 scalar_t__ XML_FEATURE_END ; 
 TYPE_1__* XML_GetFeatureList () ; 
 int XML_STATUS_ERROR ; 
 int XML_STATUS_OK ; 

__attribute__((used)) static enum XML_Status
get_feature(enum XML_FeatureEnum feature_id, long *presult)
{
    const XML_Feature *feature = XML_GetFeatureList();

    if (feature == NULL)
        return XML_STATUS_ERROR;
    for (; feature->feature != XML_FEATURE_END; feature++) {
        if (feature->feature == feature_id) {
            *presult = feature->value;
            return XML_STATUS_OK;
        }
    }
    return XML_STATUS_ERROR;
}