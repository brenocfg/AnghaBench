#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  num_buckets; int /*<<< orphan*/  num_entries; int /*<<< orphan*/  magic; } ;
struct TYPE_4__ {int bucket_size; scalar_t__ buckets; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; scalar_t__ num_buckets; scalar_t__ num_entries; } ;
typedef  int Py_ssize_t ;
typedef  char PyObject ;
typedef  TYPE_1__ HashIndex ;
typedef  TYPE_2__ HashHeader ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC ; 
 int /*<<< orphan*/  PyBUF_READ ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_ExceptionMatches (int /*<<< orphan*/ ) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_AttributeError ; 
 int /*<<< orphan*/  PyExc_OverflowError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 char* PyMemoryView_FromMemory (char*,int,int /*<<< orphan*/ ) ; 
 int PyNumber_AsSsize_t (char*,int /*<<< orphan*/ ) ; 
 char* PyObject_CallMethod (char*,char*,char*,...) ; 
 int /*<<< orphan*/  Py_DECREF (char*) ; 
 int /*<<< orphan*/  Py_XDECREF (char*) ; 
 int /*<<< orphan*/  _htole32 (scalar_t__) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 

__attribute__((used)) static void
hashindex_write(HashIndex *index, PyObject *file_py)
{
    PyObject *length_object, *buckets_view, *tmp;
    Py_ssize_t length;
    Py_ssize_t buckets_length = (Py_ssize_t)index->num_buckets * index->bucket_size;
    HashHeader header = {
        .magic = MAGIC,
        .num_entries = _htole32(index->num_entries),
        .num_buckets = _htole32(index->num_buckets),
        .key_size = index->key_size,
        .value_size = index->value_size
    };

    length_object = PyObject_CallMethod(file_py, "write", "y#", &header, (Py_ssize_t)sizeof(HashHeader));
    if(PyErr_Occurred()) {
        return;
    }
    length = PyNumber_AsSsize_t(length_object, PyExc_OverflowError);
    Py_DECREF(length_object);
    if(PyErr_Occurred()) {
        return;
    }
    if(length != sizeof(HashHeader)) {
        PyErr_SetString(PyExc_ValueError, "Failed to write header");
        return;
    }

    /*
     * Hash the header
     */
    tmp = PyObject_CallMethod(file_py, "hash_part", "s", "HashHeader");
    Py_XDECREF(tmp);
    if(PyErr_Occurred()) {
        if(PyErr_ExceptionMatches(PyExc_AttributeError)) {
            /* Be able to work with regular file objects which do not have a hash_part method. */
            PyErr_Clear();
        } else {
            return;
        }
    }

    /* Note: explicitly construct view; BuildValue can convert (pointer, length) to Python objects, but copies them for doing so */
    buckets_view = PyMemoryView_FromMemory((char*)index->buckets, buckets_length, PyBUF_READ);
    if(!buckets_view) {
        assert(PyErr_Occurred());
        return;
    }
    length_object = PyObject_CallMethod(file_py, "write", "O", buckets_view);
    Py_DECREF(buckets_view);
    if(PyErr_Occurred()) {
        return;
    }
    length = PyNumber_AsSsize_t(length_object, PyExc_OverflowError);
    Py_DECREF(length_object);
    if(PyErr_Occurred()) {
        return;
    }
    if(length != buckets_length) {
        PyErr_SetString(PyExc_ValueError, "Failed to write buckets");
        return;
    }
}