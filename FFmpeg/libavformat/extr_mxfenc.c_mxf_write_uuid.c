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
typedef  enum MXFMetadataSetType { ____Placeholder_MXFMetadataSetType } MXFMetadataSetType ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uuid_base ; 

__attribute__((used)) static void mxf_write_uuid(AVIOContext *pb, enum MXFMetadataSetType type, int value)
{
    avio_write(pb, uuid_base, 12);
    avio_wb16(pb, type);
    avio_wb16(pb, value);
}