#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum MXFMetadataSetType { ____Placeholder_MXFMetadataSetType } MXFMetadataSetType ;
struct TYPE_2__ {int /*<<< orphan*/  duration; int /*<<< orphan*/  pix_fmt; } ;
typedef  int /*<<< orphan*/  MXFMetadataSet ;
typedef  TYPE_1__ MXFDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_PIX_FMT_NONE ; 
#define  Descriptor 129 
#define  MultipleDescriptor 128 

__attribute__((used)) static int mxf_metadataset_init(MXFMetadataSet *ctx, enum MXFMetadataSetType type)
{
    switch (type){
    case MultipleDescriptor:
    case Descriptor:
        ((MXFDescriptor*)ctx)->pix_fmt = AV_PIX_FMT_NONE;
        ((MXFDescriptor*)ctx)->duration = AV_NOPTS_VALUE;
        break;
    default:
        break;
    }
    return 0;
}