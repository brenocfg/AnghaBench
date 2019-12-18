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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_Parse (int /*<<< orphan*/ *,char*,int**,int*) ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int**,int*,int**,int*,int*) ; 
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int*,int) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  manipulate (int*) ; 
 int /*<<< orphan*/  sha1_callback ; 

__attribute__((used)) static PyObject* pkg_crypt(PyObject *self, PyObject *args)
{
   uint8_t *key, *input, *ret;
   int key_length, input_length, length;
   int remaining, i, offset=0;

   PyObject *arglist;
   PyObject *result;

   if (!PyArg_ParseTuple(args, "s#s#i", &key, &key_length, &input, &input_length, &length))
      return NULL;
   ret       = malloc(length);
   remaining = length;

   while (remaining > 0)
   {
      int outHash_length;
      uint8_t *outHash;
      int bytes_to_dump = remaining;
      if (bytes_to_dump > 0x10)
         bytes_to_dump = 0x10;

      arglist = Py_BuildValue("(s#)", key, 0x40);
      result  = PyObject_CallObject(sha1_callback, arglist);
      Py_DECREF(arglist);
      if (!result)
         return NULL;
      if (!PyArg_Parse(result, "s#", &outHash, &outHash_length))
         return NULL;

      for(i = 0; i < bytes_to_dump; i++)
      {
         ret[offset] = outHash[i] ^ input[offset];
         offset++;
      }
      Py_DECREF(result);
      manipulate(key);
      remaining -= bytes_to_dump;
   }

   /* Return the encrypted data */
   PyObject *py_ret = Py_BuildValue("s#", ret, length);
   free(ret);
   return py_ret;
}