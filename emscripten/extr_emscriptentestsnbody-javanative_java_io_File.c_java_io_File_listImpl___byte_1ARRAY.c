#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; } ;
struct TYPE_8__ {int length_; char* array_; int /*<<< orphan*/  type_; } ;
struct TYPE_9__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_10__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_XMLVMArray ;
typedef  TYPE_3__* JAVA_OBJECT ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 char* XMLVMUtil_convertFromByteArray (TYPE_3__*) ; 
 void* XMLVM_MALLOC (int) ; 
 int /*<<< orphan*/  __CLASS_byte ; 
 int /*<<< orphan*/  __CLASS_org_xmlvm_runtime_XMLVMArray ; 
 scalar_t__ __NEW_org_xmlvm_runtime_XMLVMArray () ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 

JAVA_OBJECT java_io_File_listImpl___byte_1ARRAY(JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[java_io_File_listImpl___byte_1ARRAY]
	     // TODO: There may be memory management issues in this implementation
	     org_xmlvm_runtime_XMLVMArray *array =
	         (org_xmlvm_runtime_XMLVMArray *) __NEW_org_xmlvm_runtime_XMLVMArray();
	     array->fields.org_xmlvm_runtime_XMLVMArray.type_   =  __CLASS_org_xmlvm_runtime_XMLVMArray;
	     array->fields.org_xmlvm_runtime_XMLVMArray.length_ =  256;
	     array->fields.org_xmlvm_runtime_XMLVMArray.array_  = XMLVM_MALLOC(sizeof(JAVA_OBJECT) * 256);

	     JAVA_OBJECT *subarray = (JAVA_OBJECT *) array->fields.org_xmlvm_runtime_XMLVMArray.array_;

	     int i = 0;
	     for (i = 0; i < 256; i++) {
	         org_xmlvm_runtime_XMLVMArray *array2 =
	            (org_xmlvm_runtime_XMLVMArray *) __NEW_org_xmlvm_runtime_XMLVMArray();
	         array2->fields.org_xmlvm_runtime_XMLVMArray.type_   = __CLASS_byte;
	         array2->fields.org_xmlvm_runtime_XMLVMArray.length_ = 256;
	         array2->fields.org_xmlvm_runtime_XMLVMArray.array_  = XMLVM_MALLOC(sizeof(char) * 256);
	         subarray[i] = (JAVA_OBJECT) array2;
	     }

	     // Get the
	     char* fileName = XMLVMUtil_convertFromByteArray(n1);

	     DIR *d;
	     struct dirent *e;
	     if (d = opendir(fileName)) {
	         i = 0;
	         int j = 0;
	         while (e = readdir(d)) {
	             if (i < 256) { // TODO: What if there are more than 256 files?
	                 org_xmlvm_runtime_XMLVMArray *array2 = (org_xmlvm_runtime_XMLVMArray *) (subarray[i]);
	                 char *bytearray = array2->fields.org_xmlvm_runtime_XMLVMArray.array_;
	                 for (j = 0; j < 256; j++) {
	                     bytearray[j] = e->d_name[j];
	                     if (e->d_name[j] == 0) {
	                         array2->fields.org_xmlvm_runtime_XMLVMArray.length_ = j;
	                         break;
	                     }
	                 }
	                 i++;

	             }

	             // Add e->d_name to array!
	         }
	         array->fields.org_xmlvm_runtime_XMLVMArray.length_ =  i;
	         closedir(d);
	     } else {
	         // TODO: Throw IOException?
	     }
	     return array;
    //XMLVM_END_NATIVE
}