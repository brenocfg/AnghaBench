#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ array_; } ;
struct TYPE_6__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_7__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_XMLVMArray ;
struct TYPE_8__ {scalar_t__ o; } ;
typedef  TYPE_4__ XMLVMElem ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ XMLVMArray_createSingleDimension (int /*<<< orphan*/ ,int) ; 
 char* XMLVMUtil_convertFromByteArray (scalar_t__) ; 
 int /*<<< orphan*/  XMLVM_MEMCPY (char*,char*,int) ; 
 int /*<<< orphan*/  __CLASS_byte ; 
 char* readlink_malloc (char const*) ; 
 int strlen (char*) ; 

JAVA_OBJECT java_io_File_getLinkImpl___byte_1ARRAY(JAVA_OBJECT me, JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[java_io_File_getLinkImpl___byte_1ARRAY]
    const char* fileName = XMLVMUtil_convertFromByteArray(n1);
    char* resolved = readlink_malloc(fileName);
    if(resolved == NULL) {
        return n1;
    } else {
	XMLVMElem _r0;
        int length = strlen(resolved);
        _r0.o = XMLVMArray_createSingleDimension(__CLASS_byte, length);
        char* data = (char*) ((org_xmlvm_runtime_XMLVMArray*) _r0.o)->fields.org_xmlvm_runtime_XMLVMArray.array_;
        XMLVM_MEMCPY(data, resolved, length);
	return _r0.o;
    }
    //XMLVM_END_NATIVE
}