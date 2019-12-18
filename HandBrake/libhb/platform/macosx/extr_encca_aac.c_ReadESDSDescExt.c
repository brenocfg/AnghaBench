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
typedef  int /*<<< orphan*/  UInt8 ;
typedef  int UInt32 ;

/* Variables and functions */
 int MP4DecConfigDescrTag ; 
 int MP4DecSpecificDescrTag ; 
 int MP4ESDescrTag ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 long noErr ; 
 int readDescr (int /*<<< orphan*/ **,int*) ; 

__attribute__((used)) static long ReadESDSDescExt(void* descExt, UInt8 **buffer, UInt32 *size, int versionFlags)
{
    UInt8 *esds = (UInt8*)descExt;
    int tag, len;
    *size = 0;

    if (versionFlags)
        esds += 4; // version + flags
    readDescr(&esds, &tag);
    esds += 2;     // ID
    if (tag == MP4ESDescrTag)
        esds++;    // priority

    readDescr(&esds, &tag);
    if (tag == MP4DecConfigDescrTag)
    {
        esds++;    // object type id
        esds++;    // stream type
        esds += 3; // buffer size db
        esds += 4; // max bitrate
        esds += 4; // average bitrate

        len = readDescr(&esds, &tag);
        if (tag == MP4DecSpecificDescrTag)
        {
            *buffer = calloc(1, len + 8);
            if (*buffer)
            {
                memcpy(*buffer, esds, len);
                *size = len;
            }
        }
    }

    return noErr;
}