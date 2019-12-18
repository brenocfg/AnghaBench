#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jclass ;
struct TYPE_32__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetMethodID ) (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ;int /*<<< orphan*/  (* NewGlobalRef ) (TYPE_1__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* FindClass ) (TYPE_1__**,char*) ;int /*<<< orphan*/  (* GetFieldID ) (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ;int /*<<< orphan*/  (* GetJavaVM ) (TYPE_1__**,int /*<<< orphan*/ **) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  __init ; 
 int atomic_load_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store_32 (int /*<<< orphan*/ *,int) ; 
 int atomic_val_compare_exchange_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_arrayListAddFp ; 
 int /*<<< orphan*/  g_arrayListClass ; 
 int /*<<< orphan*/  g_arrayListConstructFp ; 
 int /*<<< orphan*/  g_metadataClass ; 
 int /*<<< orphan*/  g_metadataColindexField ; 
 int /*<<< orphan*/  g_metadataColnameField ; 
 int /*<<< orphan*/  g_metadataColsizeField ; 
 int /*<<< orphan*/  g_metadataColtypeField ; 
 int /*<<< orphan*/  g_metadataConstructFp ; 
 int /*<<< orphan*/  g_rowdataClass ; 
 int /*<<< orphan*/  g_rowdataClearFp ; 
 int /*<<< orphan*/  g_rowdataConstructor ; 
 int /*<<< orphan*/  g_rowdataSetBooleanFp ; 
 int /*<<< orphan*/  g_rowdataSetByteArrayFp ; 
 int /*<<< orphan*/  g_rowdataSetByteFp ; 
 int /*<<< orphan*/  g_rowdataSetDoubleFp ; 
 int /*<<< orphan*/  g_rowdataSetFloatFp ; 
 int /*<<< orphan*/  g_rowdataSetIntFp ; 
 int /*<<< orphan*/  g_rowdataSetLongFp ; 
 int /*<<< orphan*/  g_rowdataSetShortFp ; 
 int /*<<< orphan*/  g_rowdataSetStringFp ; 
 int /*<<< orphan*/  g_rowdataSetTimestampFp ; 
 int /*<<< orphan*/ * g_vm ; 
 int /*<<< orphan*/  jniTrace (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub10 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub11 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub12 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub13 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub14 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (TYPE_1__**,char*) ; 
 int /*<<< orphan*/  stub16 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub18 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub19 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,char*) ; 
 int /*<<< orphan*/  stub20 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub21 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub22 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub23 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub24 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub25 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub26 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub27 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub28 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub29 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__**,char*) ; 
 int /*<<< orphan*/  stub8 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  taosMsleep (int /*<<< orphan*/ ) ; 

void jniGetGlobalMethod(JNIEnv *env) {
  // make sure init function executed once
  switch (atomic_val_compare_exchange_32(&__init, 0, 1)) {
    case 0:
      break;
    case 1:
      do {
        taosMsleep(0);
      } while (atomic_load_32(&__init) == 1);
    case 2:
      return;
  }

  if (g_vm == NULL) {
    (*env)->GetJavaVM(env, &g_vm);
  }

  jclass arrayListClass = (*env)->FindClass(env, "java/util/ArrayList");
  g_arrayListClass = (*env)->NewGlobalRef(env, arrayListClass);
  g_arrayListConstructFp = (*env)->GetMethodID(env, g_arrayListClass, "<init>", "()V");
  g_arrayListAddFp = (*env)->GetMethodID(env, g_arrayListClass, "add", "(Ljava/lang/Object;)Z");
  (*env)->DeleteLocalRef(env, arrayListClass);

  jclass metadataClass = (*env)->FindClass(env, "com/taosdata/jdbc/ColumnMetaData");
  g_metadataClass = (*env)->NewGlobalRef(env, metadataClass);
  g_metadataConstructFp = (*env)->GetMethodID(env, g_metadataClass, "<init>", "()V");
  g_metadataColtypeField = (*env)->GetFieldID(env, g_metadataClass, "colType", "I");
  g_metadataColnameField = (*env)->GetFieldID(env, g_metadataClass, "colName", "Ljava/lang/String;");
  g_metadataColsizeField = (*env)->GetFieldID(env, g_metadataClass, "colSize", "I");
  g_metadataColindexField = (*env)->GetFieldID(env, g_metadataClass, "colIndex", "I");
  (*env)->DeleteLocalRef(env, metadataClass);

  jclass rowdataClass = (*env)->FindClass(env, "com/taosdata/jdbc/TSDBResultSetRowData");
  g_rowdataClass = (*env)->NewGlobalRef(env, rowdataClass);
  g_rowdataConstructor = (*env)->GetMethodID(env, g_rowdataClass, "<init>", "(I)V");
  g_rowdataClearFp = (*env)->GetMethodID(env, g_rowdataClass, "clear", "()V");
  g_rowdataSetBooleanFp = (*env)->GetMethodID(env, g_rowdataClass, "setBoolean", "(IZ)V");
  g_rowdataSetByteFp = (*env)->GetMethodID(env, g_rowdataClass, "setByte", "(IB)V");
  g_rowdataSetShortFp = (*env)->GetMethodID(env, g_rowdataClass, "setShort", "(IS)V");
  g_rowdataSetIntFp = (*env)->GetMethodID(env, g_rowdataClass, "setInt", "(II)V");
  g_rowdataSetLongFp = (*env)->GetMethodID(env, g_rowdataClass, "setLong", "(IJ)V");
  g_rowdataSetFloatFp = (*env)->GetMethodID(env, g_rowdataClass, "setFloat", "(IF)V");
  g_rowdataSetDoubleFp = (*env)->GetMethodID(env, g_rowdataClass, "setDouble", "(ID)V");
  g_rowdataSetStringFp = (*env)->GetMethodID(env, g_rowdataClass, "setString", "(ILjava/lang/String;)V");
  g_rowdataSetTimestampFp = (*env)->GetMethodID(env, g_rowdataClass, "setTimestamp", "(IJ)V");
  g_rowdataSetByteArrayFp = (*env)->GetMethodID(env, g_rowdataClass, "setByteArray", "(I[B)V");
  (*env)->DeleteLocalRef(env, rowdataClass);

  atomic_store_32(&__init, 2);
  jniTrace("native method register finished");
}