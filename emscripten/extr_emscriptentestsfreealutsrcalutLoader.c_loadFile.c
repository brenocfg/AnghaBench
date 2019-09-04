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
typedef  int Int32BigEndian ;
typedef  int /*<<< orphan*/  InputStream ;
typedef  int /*<<< orphan*/  BufferData ;

/* Variables and functions */
 int /*<<< orphan*/  ALUT_ERROR_UNSUPPORTED_FILE_TYPE ; 
 int /*<<< orphan*/ * AL_FALSE ; 
 char* _alutInputStreamGetFileName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _alutInputStreamReadInt32BE (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 
 scalar_t__ hasSuffixIgnoringCase (char const*,char*) ; 
 int /*<<< orphan*/ * loadAUFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * loadRawFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * loadWavFile (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BufferData *loadFile(InputStream * stream)
{
  const char *fileName;
  Int32BigEndian magic;

  /* Raw files have no magic number - so use the fileName extension */

  fileName = _alutInputStreamGetFileName(stream);
  if (fileName != NULL && hasSuffixIgnoringCase(fileName, ".raw"))
  {
    return loadRawFile(stream);
  }

  /* For other file formats, read the quasi-standard four byte magic number */
  if (!_alutInputStreamReadInt32BE(stream, &magic))
  {
    return AL_FALSE;
  }

  /* Magic number 'RIFF' == Microsoft '.wav' format */
  if (magic == 0x52494646)
  {
    return loadWavFile(stream);
  }

  /* Magic number '.snd' == Sun & Next's '.au' format */
  if (magic == 0x2E736E64)
  {
    return loadAUFile(stream);
  }

  _alutSetError(ALUT_ERROR_UNSUPPORTED_FILE_TYPE);
  return AL_FALSE;
}