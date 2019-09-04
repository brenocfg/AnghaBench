#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length_; scalar_t__ array_; } ;
struct TYPE_7__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_8__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_XMLVMArray ;
typedef  TYPE_3__* JAVA_OBJECT ;

/* Variables and functions */
 char* XMLVM_ATOMIC_MALLOC (int) ; 
 int /*<<< orphan*/  XMLVM_MEMCPY (char*,char*,int) ; 

char* XMLVMUtil_convertFromByteArray(JAVA_OBJECT byteArray) {
    org_xmlvm_runtime_XMLVMArray* a = byteArray;
    char* data = (char*) a->fields.org_xmlvm_runtime_XMLVMArray.array_;
    int length = a->fields.org_xmlvm_runtime_XMLVMArray.length_;
    char* buf = XMLVM_ATOMIC_MALLOC(length + 1);
    XMLVM_MEMCPY(buf, data, length);
    buf[length] = '\0';
    return buf;
}